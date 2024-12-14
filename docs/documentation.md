# Universe Project Documentation

The **Universe** project is built as a **static library** to provide core functionality for client applications. The library contains foundational systems such as the application lifecycle, logging, and rendering.

Client applications include:
- **Forge**: The editor with a graphical interface.
- **Sandbox**: The runtime for executing game logic and simulations.

## **Classes**

### 1. `Universe::Application`
#### Purpose
The `Application` class is the central manager for the application's lifecycle. It provides the main loop and ensures proper initialization and shutdown of the application.

#### Key Responsibilities
- Acts as the base class for client applications (e.g., Forge or Sandbox).
- Contains the `Run()` method, which serves as the main application loop.
- Manages application state through the `m_IsRunning` flag.

#### Methods
- **Constructor (`Application()`)**:
  - Initializes the application. No user intervention is required.
- **Destructor (`~Application()`)**:
  - Ensures proper cleanup of resources when the application is destroyed.
- **`Run()`**:
  - Executes the main loop of the application. The loop continues until `m_IsRunning` is set to `false`.
- **`Create()` (Factory Method)**:
  - Declared in the library but implemented by client applications.
  - Example: The Forge application implements this to return a `Forge` instance.

---

## **Entry Point**
The Universe library includes a predefined `main()` function in its entry point header. This function is designed to simplify the creation of client applications.

#### Purpose
The `main()` function:
- Calls the factory method `Universe::Create()` to create an instance of the client application.
- Starts the main loop of the application using the `Run()` method.
- Cleans up the application by deleting the instance after the loop ends.

#### Flow
1. `Universe::Create()` is called to instantiate the client application.
2. `Run()` is executed to start the main loop.
3. After exiting the loop, the application instance is destroyed with `delete`.

#### Notes
- The actual implementation of `Universe::Create()` must be provided by the client application (e.g., Forge or Sandbox).
- The `main()` function itself is part of the Universe library but only acts as a template for the client.

## **Design Considerations**
1. **Static Library**: The Universe library is built as a static library, meaning it is linked to client applications at compile time. This allows flexibility for each client to define its own behavior while using the core functionality of Universe.

2. **Centralized Header (`universe.hpp`)**:
   - Serves as a convenience header for client applications.
   - Includes all key components of the Universe library.

3. **Separation of Concerns**:
   - The library provides core systems and lifecycle management.
   - Client applications implement custom functionality (e.g., Forge's GUI or Sandbox's runtime logic).

## **How to Use Universe in a Client Application**
1. **Include the Entry Point**:
   - Client applications should include `universe.hpp` for access to the core engine functionality.
2. **Implement the Factory Method**:
   - Define `Universe::Create()` in the client application to return an instance of the specific application class.

   Example:
   ```cpp
   Universe::Application* Universe::Create()
   {
       return new Forge();
   }
   ```
3. **Run the Application**:
   - The `main()` function in Universe will handle the lifecycle:
     - It creates the application instance via `Create()`.
     - Runs the application loop with `Run()`.
     - Cleans up resources after the loop.
