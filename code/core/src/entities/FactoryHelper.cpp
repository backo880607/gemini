#include "entities/FactoryHelper.h"
#include "Application.h"
#include "tools/XML.h"
#include "tools/File.h"
#include "entities/FactoryMgr.h"
#include "message/Exception.h"
#include "tools/StringUtil.h"

namespace gemini {

FactoryHelper::FactoryHelper()
{

}

FactoryHelper::~FactoryHelper()
{

}

void FactoryHelper::loadConfig()
{
	FilePath path = g_app.getConfigPath();
	path.append(u8"relations");
	XMLFile::foreach_recursion(path.string().c_str(), [&](XMLFile& xmlFile) {
		XMLNode rootNode = xmlFile.getNode(u8"Class");
		THROW_IF(!rootNode.valid(), Exception, u8" relations xml config invalid class node: ")
		String clsName = rootNode.getAttribute(u8"name");
		EntityFactory* firstFactory = FactoryMgr::instance().getFactory(clsName);
		THROW_IF(firstFactory == nullptr, Exception, u8"invalid bean name: ", clsName)
		rootNode.foreach([&](XMLNode relaNode) {
			String firstSignName = relaNode.getAttribute(u8"field");
			Int firstSign = firstFactory->getRelaSign(firstSignName);
			THROW_IF(firstSign == 0, Exception, u8"invalid field name: ", firstSignName, u8" which bean is: ", clsName)
			String secondFactoryName = relaNode.getAttribute(u8"name");
			EntityFactory* secondFactory = FactoryMgr::instance().getFactory(secondFactoryName);
			THROW_IF(secondFactory == nullptr, Exception, u8"invalid bean name: ", secondFactoryName)
			String secondSignName = relaNode.getAttribute(u8"reverse");
			Int secondSign = secondFactory->getRelaSign(secondSignName);
			THROW_IF(secondSign == 0, Exception, u8"invalid field name: ", secondSignName, u8" which bean is: ", secondFactoryName)
			EntityFactory::Data* firstData = const_cast<EntityFactory::Data*>(firstFactory->getRelaData(firstSign));
			THROW_IF(firstData == nullptr, Exception, u8"entity factory relaData init failed.")
			firstData->relaFactory = secondFactory;
			firstData->reverseSign = secondSign;

			String relaName = relaNode.getAttribute(u8"rela");
			EntityFactory::Relation rela = EntityFactory::Relation::OneToMulti;
			firstData->rela = rela;

			String typeName = relaNode.getAttribute(u8"type");
			EntityFactory::RefType type = typeName.empty() ? EntityFactory::RefType::T_List : EntityFactory::RefType::T_Set;
			switch (rela)
			{
			case EntityFactory::Relation::OneToOne:
				firstData->type = EntityFactory::RefType::T_Singleton;
				break;
			case EntityFactory::Relation::OneToMulti:
				firstData->type = type;
				break;
			case EntityFactory::Relation::MultiToOne:
				firstData->type = EntityFactory::RefType::T_Singleton;
				break;
			case EntityFactory::Relation::MultiToMulti:
				firstData->type = type;
				break;
			default:
				break;
			}

			String ownerName = relaNode.getAttribute(u8"owner");
			firstData->owner = StringUtil::icompare(ownerName.c_str(), u8"true") == 0 ? true : false;

			// �з������
			if (secondSign > 0) {
				EntityFactory::Data* secondData = const_cast<EntityFactory::Data*>(secondFactory->getRelaData(secondSign));
				THROW_IF(secondData == nullptr, Exception, u8"entity factory relaData init failed.")
				secondData->relaFactory = firstFactory;
				secondData->reverseSign = firstSign;
				secondData->owner = false;
				switch (rela)
				{
				case EntityFactory::Relation::OneToOne:
					secondData->rela = EntityFactory::Relation::OneToOne;
					secondData->type = EntityFactory::RefType::T_Singleton;
					break;
				case EntityFactory::Relation::OneToMulti:
					secondData->rela = EntityFactory::Relation::MultiToOne;
					secondData->type = EntityFactory::RefType::T_Singleton;
					break;
				case EntityFactory::Relation::MultiToOne:
					secondData->rela = EntityFactory::Relation::OneToMulti;
					secondData->type = type;
					break;
				case EntityFactory::Relation::MultiToMulti:
					secondData->rela = EntityFactory::Relation::MultiToMulti;
					secondData->type = firstData->type;
					break;
				default:
					break;
				}
			}
		});
	});
}

}