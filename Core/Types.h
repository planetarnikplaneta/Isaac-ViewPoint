struct Vertex3
    {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    };

    struct Vertex2
    {
        float u = 0.0f;
        float v = 0.0f;
    };

    struct ObjCorner
    {
        int32_t position = -1;
        int32_t texcoord = -1;
        int32_t normal = -1;
    };

    struct Triangle
    {
        ObjCorner corners[3];
        int materialIndex = 0;
    };

    struct Material
    {
        std::string name;

        float ambient[3] = {
            0.2f, 0.2f, 0.2f};

        float diffuse[3] = {
            1.0f, 1.0f, 1.0f};

        float specular[3] = {
            0.0f, 0.0f, 0.0f};

        float shininess = 32.0f;

        std::string diffuseTexturePath;

        std::vector<unsigned char> pixels;

        int width = 0;
        int height = 0;

        GLuint textureId = 0;

        bool textureAttempted = false;
    };

    struct GpuVertex
    {
        Vertex3 position;
        Vertex3 normal;
        Vertex2 texcoord;
    };

    struct MaterialBatch
    {
        GLuint vertexBuffer = 0;
        GLsizei vertexCount = 0;
        int materialIndex = 0;
    };

    // Every model owns its own geometry and materials.
    struct Model
    {
        std::string path;

        std::vector<Vertex3> vertices;
        std::vector<Vertex2> texcoords;
        std::vector<Vertex3> normals;

        std::vector<Triangle> triangles;
        std::vector<Material> materials;

        std::vector<MaterialBatch> gpuBatches;

        bool gpuBuildAttempted = false;
        bool gpuReady = false;

        // Instance transformation.
        Vertex3 position = {0.0f, 0.0f, 0.0f};
        Vertex3 rotation = {0.0f, 0.0f, 0.0f};

        float scale = 1.0f;

        bool attempted = false;
        bool loaded = false;
    };

    struct ObjectConfig
    {
        std::string path;

        Vertex3 position = {0.0f, 0.0f, 0.0f};
        Vertex3 rotation = {0.0f, 0.0f, 0.0f};

        float scale = 1.0f;
    };

    struct Camera
    {
        Vertex3 position = {0.0f, 0.0f, 5.0f};

        float yaw = 0.0f;
        float pitch = 0.0f;

        float fieldOfView = 45.0f;
        float nearPlane = 0.1f;
        float farPlane = 1000.0f;

        float movementSpeed = 5.0f;
        float sprintMultiplier = 3.0f;
        float mouseSensitivity = 0.15f;

        bool enabled = false;
        bool previousF1State = false;

        ULONGLONG lastUpdateTime = 0;
    };
