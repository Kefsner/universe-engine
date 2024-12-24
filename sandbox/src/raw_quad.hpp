#include <universe.hpp>

class RawQuad : public Universe::Layer
{
public:
    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Universe::Timestep ts) override;
    virtual void OnEvent(Universe::Event& event) override;

private:
    uint32_t m_VertexArray;
    uint32_t m_IndexCount;
};