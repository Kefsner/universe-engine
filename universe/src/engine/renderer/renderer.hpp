namespace Universe {

    class Renderer {
    public:
        static void Init();
        static void Shutdown();
        static void BeginScene();
        static void Submit();
        static void EndScene();
    };
}