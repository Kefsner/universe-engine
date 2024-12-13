#pragma once

#include "universe/renderer/framebuffer.hpp"

namespace Universe {

    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        OpenGLFramebuffer(const FramebufferSpecification& spec);
        virtual ~OpenGLFramebuffer();

        void Invalidate();

        void Bind() const override;
        void Unbind() const override;

        uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }

        const FramebufferSpecification& GetSpecification() const override { return m_Specification; }

    private:
        FramebufferSpecification m_Specification;
        uint32_t m_RendererID;
        uint32_t m_ColorAttachment;
        uint32_t m_DepthAttachment;
    };
}