#include "propagate/PropagateHelper.h"
#include "propagate/Propagate.h"
#include "entities/FactoryMgr.h"
#include "Application.h"
#include "tools/XML.h"
#include "tools/File.h"
#include "message/Exception.h"
#include "service/ServiceMgr.h"
#include "tools/StringUtil.h"

namespace gemini {

PropagateHelper::PropagateHelper()
{

}

PropagateHelper::~PropagateHelper()
{

}

void PropagateHelper::loadConfig()
{
	FilePath path = g_app.getConfigPath();
	path.append(u8"propagate");
	XMLFile::foreach_recursion(path.string().c_str(), [&](XMLFile& xmlFile) {
		XMLNode rootNode = xmlFile.getNode(u8"Class");
		THROW_IF(!rootNode.valid(), Exception, u8"invalid config file: ")

		String clsName = rootNode.getAttribute(u8"name");
		EntityFactory* factory = FactoryMgr::instance().getFactory(clsName);
		THROW_IF(factory == nullptr, Exception, u8"invalid bean name: ", clsName)
		
		XMLNode propertyNode = rootNode.getNode(u8"property");
		THROW_IF(!propertyNode.valid(), Exception, u8"invalid property node: ", clsName)

		propertyNode.foreach([&](XMLNode propertyNode) {
			String propertyName = propertyNode.getAttribute(u8"name");
			const Field& field = factory->getEntityClass().getField(propertyName);
			Propagate::Data& data = Propagate::instance()._datas[factory->getEntityClass().index()][&field];

			String srvName;
			XMLNode srvNode = propertyNode.getNode(u8"serviceClass");
			if (srvNode.valid()) {
				srvName = srvNode.getValue();
			}
			if (srvName.empty()) {
				srvName = clsName + u8"Service";
			}
			data.service = ServiceMgr::instance().get(srvName);

			XMLNode funNode = propertyNode.getNode(u8"function");
			THROW_IF(!funNode.valid(), Exception, u8"invalid function node: ", clsName)
			String funName = funNode.getValue();
			data.method = ServiceMgr::instance().getCallers(srvName, funName);

			XMLNode dependencesNode = propertyNode.getNode(u8"dependences");
			THROW_IF(!dependencesNode.valid(), Exception, u8"lost the dependence path: ", clsName)
			dependencesNode.foreach([&](XMLNode depNode) {
				String strDep = depNode.getValue();
				std::vector<UInt> pathSigns;
				Boolean bLastField = false;
				StringUtil::parse<String>(strDep, u8";", [&](const String& strField) {
					THROW_IF(bLastField, Exception, u8"invalid dependence path: ", strDep)
					std::vector<String> fields;
					StringUtil::parse<String>(fields, strField, u8".");
					THROW_IF(fields.size() != 2, Exception, u8"invalid dependence path: ", strField)
					EntityFactory* depFactory = FactoryMgr::instance().getFactory(fields[0]);
					THROW_IF(depFactory == nullptr, Exception, u8"invalid dependence path: ", strField)
					const Field& field = depFactory->getEntityClass().getField(fields[1]);
					if (field.index() > 0) {
						pathSigns.push_back(field.index());
					} else {
						data.paths.push_back(pathSigns);
						data.properties.push_back(&field);
						bLastField = true;
					}
				});
			});
		});
	});
}

}