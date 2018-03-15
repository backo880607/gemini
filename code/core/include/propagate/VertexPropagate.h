#ifndef GEMINI_VertexPropagate_INCLUDE
#define GEMINI_VertexPropagate_INCLUDE
#include "../graph/Vertex.h"
#include "Propagate.h"

namespace gemini {

class VertexPropagate final : public graph::Vertex
{
public:
	struct Comparator {
		inline Boolean operator() (const VertexPropagate* const& lhs, const VertexPropagate* const& rhs) const {
			if (lhs->_entity == rhs->_entity) {
				return lhs->_data->id < rhs->_data->id;
			}
			return lhs->_entity < rhs->_entity;
		}
	};
	typedef std::set<VertexPropagate*, VertexPropagate::Comparator> colls;
public:
	VertexPropagate();
	~VertexPropagate();

	virtual graph::Graph* createGraph();

	const Propagate::Data* getData() const { return _data; }

	const EntityObject::SPtr& getEntityObject() const { return _entity; }

	VertexPropagate* createVertex(const EntityObject::SPtr& entity, const Propagate::Data* data);
	VertexPropagate* getVertex(const EntityObject::SPtr& entity, const Propagate::Data* data);

public:
	Short _visited;

private:
	EntityObject::SPtr _entity;
	const Propagate::Data* _data;
};

}

#endif