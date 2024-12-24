#include <universe.hpp>

class RawQuad : public Universe::Layer
{
public:
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Universe::Timestep ts) override;
    virtual void OnEvent(Universe::Event& event) override;

private:
    unsigned int m_VertexArray;
    unsigned int m_IndexCount;
};