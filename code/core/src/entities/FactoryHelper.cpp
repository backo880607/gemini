#include "entities/FactoryHelper.h"
#include "Application.h"
#include "entities/FactoryMgr.h"
#include "message/Exception.h"
#include "tools/File.h"
#include "tools/StringUtil.h"
#include "tools/XML.h"

namespace gemini {

FactoryHelper::FactoryHelper() {}

FactoryHelper::~FactoryHelper() {}

void FactoryHelper::loadConfig() {
  FilePath path = g_app.getConfigPath();
  path.append("relations");
  XMLFile::foreach_recursion(path.string().c_str(), [&](XMLFile& xmlFile) {
    XMLNode rootNode = xmlFile.getNode("Class");
    THROW_IF(!rootNode.valid(), Exception,
             " relations xml config invalid class node: ")
    String clsName = rootNode.getAttribute("name");
    EntityFactory* firstFactory = FactoryMgr::instance().getFactory(clsName);
    THROW_IF(firstFactory == nullptr, Exception, "invalid bean name: ", clsName)
    rootNode.foreach ([&](XMLNode relaNode) {
      String firstSignName = relaNode.getAttribute("field");
      Int firstSign = firstFactory->getRelaSign(firstSignName);
      THROW_IF(firstSign == 0, Exception, "invalid field name: ", firstSignName,
               " which bean is: ", clsName)
      String secondFactoryName = relaNode.getAttribute("relaClass");
      EntityFactory* secondFactory =
          FactoryMgr::instance().getFactory(secondFactoryName);
      THROW_IF(secondFactory == nullptr, Exception,
               "invalid bean name: ", secondFactoryName)
      String secondSignName = relaNode.getAttribute("relaField");
      Int secondSign = secondFactory->getRelaSign(secondSignName);
      THROW_IF(secondSign == 0, Exception,
               "invalid field name: ", secondSignName,
               " which bean is: ", secondFactoryName)
      EntityFactory::Data* firstData = const_cast<EntityFactory::Data*>(
          firstFactory->getRelaData(firstSign));
      THROW_IF(firstData == nullptr, Exception,
               "entity factory relaData init failed.")
      firstData->relaFactory = secondFactory;
      firstData->relaSign = secondSign;

      String relaName = relaNode.getAttribute("rela");
      if (StringUtil::icompare(relaName.c_str(), "OneToOne") == 0) {
        firstData->rela = EntityFactory::Relation::OneToOne;
      } else if (StringUtil::icompare(relaName.c_str(), "OneToMulti") == 0) {
        firstData->rela = EntityFactory::Relation::OneToMulti;
      } else if (StringUtil::icompare(relaName.c_str(), "MultiToOne") == 0) {
        firstData->rela = EntityFactory::Relation::MultiToOne;
      } else if (StringUtil::icompare(relaName.c_str(), "MultiToMulti") == 0) {
        firstData->rela = EntityFactory::Relation::MultiToMulti;
      } else {
        THROW(Exception, "invalid rela: ", relaName);
      }

      String ownerName = relaNode.getAttribute("owner");
      firstData->owner =
          StringUtil::icompare(ownerName.c_str(), "true") == 0 ? true : false;

      firstData->storage = true;

      // �з������
      if (secondSign > 0) {
        EntityFactory::Data* secondData = const_cast<EntityFactory::Data*>(
            secondFactory->getRelaData(secondSign));
        THROW_IF(secondData == nullptr, Exception,
                 "entity factory relaData init failed.")
        secondData->relaFactory = firstFactory;
        secondData->relaSign = firstSign;
        secondData->owner = false;
        secondData->storage = false;
        switch (firstData->rela) {
          case EntityFactory::Relation::OneToOne:
            secondData->rela = EntityFactory::Relation::OneToOne;
            break;
          case EntityFactory::Relation::OneToMulti:
            secondData->rela = EntityFactory::Relation::MultiToOne;
            secondData->storage = true;
            firstData->storage = false;
            break;
          case EntityFactory::Relation::MultiToOne:
            secondData->rela = EntityFactory::Relation::OneToMulti;
            break;
          case EntityFactory::Relation::MultiToMulti:
            secondData->rela = EntityFactory::Relation::MultiToMulti;
            break;
          default:
            break;
        }
      }
    });
  });
}

}  // namespace gemini