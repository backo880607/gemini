#include "../../include/propagate/Propagate.h"
#include "../../include/propagate/VertexPropagate.h"
#include "../../include/propagate/GraphPropagate.h"
#include "../../include/entities/IocRelation.h"

#include <stack>

namespace gemini {

MT_UInt Propagate::s_maxID(0);
Propagate::Propagate()
	: _datas(Class::max_limits())
{
}

Propagate::~Propagate()
{

}

void getEntities(const EntityObject::SPtr& entity, std::vector<UInt>::const_iterator iter, const std::vector<UInt>& signs,
	std::set<EntityObject::SPtr>& result)
{
	if (iter == signs.end()) {
		result.insert(entity);
	}
	else {
		IList::Iterator relaIter = IocRelation::getList(entity, *iter++)->iterator();
		while (relaIter.hasNext()) {
			getEntities(relaIter.next<EntityObject>(), iter, signs, result);
		}
	}
}

std::vector<VertexPropagate*> buildVertex(VertexPropagate* trigger) 
{
	trigger->_visited = -1;
	std::vector<VertexPropagate*> result;
	const Propagate::Data* triggerData = trigger->getData();
	if (triggerData == nullptr) {
		return result;
	}

	UInt index = 0;
	for (const std::vector<UInt>& path : triggerData->paths) {
		std::set<EntityObject::SPtr> entities;
		getEntities(trigger->getEntityObject(), path.begin(), path, entities);

		const Propagate::Data* targetData = Propagate::instance().getData(triggerData->properties[index]);
		for (const EntityObject::SPtr& entity : entities) {
			VertexPropagate* target = trigger->getVertex(entity, targetData);
			if (target == nullptr) {
				target = trigger->createVertex(entity, targetData);
				result.push_back(target);
			} else if (target->_visited == -1) { // ³öÏÖÑ­»·

			} else {
				graph::Graph::createEdge(trigger, 0, target, -1);
			}
		}
		++index;
	}
	return result;
}

std::shared_ptr<GraphPropagate> buildGraph(VertexPropagate::colls& originPts) 
{
	std::shared_ptr<GraphPropagate> graph(new GraphPropagate());
	for (VertexPropagate::colls::iterator iter = originPts.begin();
		iter != originPts.end(); ) {
		VertexPropagate* vertex = *iter;
		if (graph->get(vertex) != nullptr) {
			iter = originPts.erase(iter);
			continue;
		}
		
		graph->getNode(vertex, true);
		graph->add(vertex);

		std::stack<VertexPropagate*> triggerQueue;
		triggerQueue.push(vertex);
		while (!triggerQueue.empty()) {
			VertexPropagate* curTrigger = triggerQueue.top();
			std::vector<VertexPropagate*> targets = buildVertex(curTrigger);
			if (targets.empty()) {
				curTrigger->_visited = 1;
				triggerQueue.pop();
			} else {
				for (VertexPropagate* target : targets) {
					triggerQueue.push(target);
				}
			}
		}
		++iter;
	}

	return graph;
}

void Propagate::invoke()
{
}

void Propagate::modify(const EntityObject::SPtr & entity, const Field * field)
{

}

Propagate::Data* Propagate::getData(const Field * field)
{
	return &(_datas[field->getClass().index()][field]);
}

}