🎯 Project Purpose
The tUI (Terminal User Interface) framework allows for quick and easy creation of terminal user interfaces without needing in-depth knowledge of the underlying ncurses library.

🧩 Core Components
libtui: Library that wraps the ncurses API and provides predefined graphical elements (panels, buttons, text fields) with an event management engine.

tbuild: Compiler that translates an interface description in XML format into compilable C source code.

tUI: Graphical application (built with libtui) for visually designing interfaces. Also serves as a demonstrator.

🎨 Model and Views
The application is structured around views, which can be of three types:

Panel (Panel): Canvas containing components such as labels (Label), buttons (Button), checkboxes (Check-button), selection lists (List-button), and input fields (Field).

Table (Table): For displaying data in a tabular format.

Editor (Edit): Simple text editor for files.

🔄 View Life Cycle
Each view goes through defined states: Creation → Display → Activation → Deactivation → Hiding/Destruction. This cycle is managed by the library.

🎮 Events and Navigation
Handles keyboard events (Enter, Out, Up, Down, Tab, Esc, Function keys F1-F12) and, optionally, mouse events.

Navigation between elements is defined by movement attributes (Move) in the XML, specifying which view or element to switch to when an event occurs.

⚙️ Configuration and XML
The application is configured through a main XML file that defines:

Project properties: Use of color, mouse, error handling, characters for checkboxes, border styles.

Views and components: Panels, buttons, fields, lists, tables, and editors, with their dimensions, position, color, and associated events.

User functions (Callbacks): C functions executed in response to events (e.g., clicking a button) or at specific points in the life cycle.

Keyboard maps (Keymaps): For customizing key-to-event mappings.

Colors and styles: Define the appearance of elements.

🛠️ Typical Development Workflow
Design: Use the graphical tool tUI or manually edit the XML to define the interface.

Generation: Execute tbuild my_project.xml to generate the .c and .h files.

Programming: Implement the application logic in the generated callback functions (in *_func.c).

Compilation: Compile the generated files, linking them with libtui and ncurses.

💻 Core Programming API
The library provides functions to interact with components from C code, such as:

COMPONENT_getValue() / COMPONENT_setValue(): Get or set the value of a component.

LVIEW_getElement(): Get a reference to any view or component by its name.

MSG_create(): Display pop-up information, warning, or error windows.

TEXT_*(): Low-level functions for manipulating data in table or editor views.

✨ Conclusion
tUI is a complete system that abstracts the complexity of ncurses, enabling developers to create feature-rich terminal applications through the combination of a declarative description (XML) and programmatic logic (C). It is ideal for creating menus, forms, data viewers, and editors within the terminal.
