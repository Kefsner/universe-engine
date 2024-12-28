#include "sandbox2D.hpp"

void Sandbox2D::OnAttach()
{
    Universe::Renderer2D::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    m_BackgroundTexture = Universe::Texture2D::Create("sandbox/assets/textures/background.png");
    m_StartButtonTexture = Universe::Texture2D::Create("sandbox/assets/textures/start_button.png");
    m_ExitButtonTexture = Universe::Texture2D::Create("sandbox/assets/textures/exit_button.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Universe::Timestep ts)
{
    if (m_GameIsRunning)
    {
        UE_TRACE("Woohoo! The game is running!");

        if (Universe::Input::IsKeyPressed(Universe::Key::Right))
        {
            Universe::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f });
        }

        if (Universe::Input::IsKeyPressed(Universe::Key::Left))
        {
            Universe::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 0.5f, 0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f });
        }

        if (Universe::Input::IsKeyPressed(Universe::Key::Up))
        {
            Universe::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f });
        }

        if (Universe::Input::IsKeyPressed(Universe::Key::Down))
        {
            Universe::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 0.5f, 0.5f }, { 1.0f, 1.0f, 0.0f, 1.0f });
        }

        if (Universe::Input::IsKeyPressed(Universe::Key::Space))
        {
            Universe::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 0.5f, 0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f });
        }

        return;
    }
    glm::vec4 start_button_tint = { 1.0f, 1.0f, 1.0f, 1.0f };
    glm::vec4 exit_button_tint = { 0.5f, 0.5f, 0.5f, 1.0f };

    Universe::Renderer2D::BeginScene();
    Universe::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 2.0f, 2.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, m_BackgroundTexture);

    if (!m_StartButtonSelected)
    {
        start_button_tint = { 0.5f, 0.5f, 0.5f, 1.0f };
        exit_button_tint = { 1.0f, 1.0f, 1.0f, 1.0f };
    }  

    Universe::Renderer2D::DrawQuad({-0.4f, 0.0f }, { 0.4f, 0.4f }, start_button_tint, m_StartButtonTexture);
    Universe::Renderer2D::DrawQuad({ 0.4f, 0.0f }, { 0.4f, 0.4f }, exit_button_tint, m_ExitButtonTexture);
    
    Universe::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Universe::Event& event)
{
    Universe::EventDispatcher dispatcher(event);
    dispatcher.Dispatch<Universe::KeyPressedEvent>(UE_BIND_EVENT_FN(Sandbox2D::OnKeyPressed));
}

bool Sandbox2D::OnKeyPressed(Universe::KeyPressedEvent& event)
{
    if (event.GetKeyCode() == Universe::Key::Left || event.GetKeyCode() == Universe::Key::Right)
    {
        m_StartButtonSelected = !m_StartButtonSelected;
    }

    if (event.GetKeyCode() == Universe::Key::Enter)
    {
        if (m_StartButtonSelected)
        {
            m_GameIsRunning = true;
        }
        else
        {
            // Ask if the user wants to exit the game]
            UE_TRACE("Bye bye!");
        }
    }

    if (m_GameIsRunning && event.GetKeyCode() == Universe::Key::Escape)
    {
        m_GameIsRunning = false;
    }

    return true; // Event handled
}

