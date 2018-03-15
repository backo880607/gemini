#include "../../include/propagate/PropagateHelper.h"
#include "../../include/propagate/Propagate.h"
#include "../../include/entities/FactoryMgr.h"
#include "../../include/Application.h"
#include "../../public/tools/XML.h"
#include "../../public/tools/File.h"
#include "../../public/message/Exception.h"
#include "../../include/service/ServiceMgr.h"
#include "../../public/tools/StringUtil.h"

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
		if (!rootNode.valid()) {
			THROW(Exception) << u8"invalid config file: ";
		}

		String clsName = rootNode.getAttribute(u8"name");
		EntityFactory* factory = FactoryMgr::instance().getFactory(clsName);
		if (factory == nullptr) {
			THROW(Exception) << u8"invalid bean name: " << clsName;
		}
		
		XMLNode propertyNode = rootNode.getNode(u8"property");
		if (!propertyNode.valid()) {
			THROW(Exception) << u8"invalid property node: " << clsName;
		}

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
			if (!funNode.valid()) {
				THROW(Exception) << u8"invalid function node: " << clsName;
			}
			String funName = funNode.getValue();
			data.method = ServiceMgr::instance().getCallers(srvName, funName);

			XMLNode dependencesNode = propertyNode.getNode(u8"dependences");
			if (!dependencesNode.valid()) {
				THROW(Exception) << u8"lost the dependence path: " << clsName;
			}
			dependencesNode.foreach([&](XMLNode depNode) {
				String strDep = depNode.getValue();
				std::vector<UInt> pathSigns;
				Boolean bLastField = false;
				StringUtil::parse<String>(strDep, u8";", [&](const String& strField) {
					if (bLastField) {
						THROW(Exception) << u8"invalid dependence path: " << strDep;
					}

					std::vector<String> fields;
					StringUtil::parse<String>(fields, strField, u8".");
					if (fields.size() != 2) {
						THROW(Exception) << u8"invalid dependence path: " << strField;
					}

					EntityFactory* depFactory = FactoryMgr::instance().getFactory(fields[0]);
					if (depFactory == nullptr) {
						THROW(Exception) << u8"invalid dependence path: " << strField;
					}

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