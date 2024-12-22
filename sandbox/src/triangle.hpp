#include <universe.hpp>

class Triangle : public Universe::Layer
{
public:
     Triangle() = default;
    ~Triangle() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnUpdate(Universe::Timestep ts) override;
    virtual void OnEvent(Universe::Event& event) override;

private:
    Universe::Ref<Universe::VertexArray> m_VertexArray;
};