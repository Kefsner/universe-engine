#include <universe.hpp>

class RawTriangle : public Universe::Layer
{
public:
     RawTriangle() = default;
    ~RawTriangle() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Universe::Timestep ts) override;
    virtual void OnEvent(Universe::Event& event) override;

private:
    uint32_t m_VertexArray;
};