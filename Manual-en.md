# Introduction
The TUI project consists of the libtui library, an ncurses wrapper, the tbuild compiler that translates XML to source files, and the tUI graphical application.

# Model
The project features three view types:
1. **Panel**: Includes elements such as labels, buttons, checkbuttons, listbuttons, and fields.
2. **Table**: Used for displaying tabulated data.
3. **Edit**: A simple text editor.

# Lifecycle
The lifecycle of the application is divided into several states:
1. **Creation**: Initial setup of the application.
2. **Mostrado**: The shown state when the application is active.
3. **Activation**: The application becomes responsive to user input.
4. **Deactivation**: The application is inactive but retains its state.
5. **Ocultacion**: The application is hidden.
6. **Destruction**: The cleanup and release of resources.

# Events
This section documents the keyboard and mouse events:
- **Keyboard Events**: Enter, Out, Up, Down, Left, Right, Next, Previous, Fn.
- **Mouse Events**: Various interactions using the mouse.

# General Aspects
## Properties
1. **Color**: Manage and use color settings.
2. **Mouse**: Mouse interactions and their handling.
3. **Errors**: How errors are managed within the application.
4. **Check buttons**: Functionality related to check buttons.
5. **Borders**: Configurations related to borders in UI elements.
6. **User**: Main user interactions and configurations.
7. **Init View**: Settings for initial view configurations.

# Keymap
The keymap section covers custom keyboard mapping and how users can define their own shortcuts.

# Ed Functions
This section provides insights into field validation and transformation functions for user entries.

# Colors
It discusses color definitions used within the application, including ncurses color options and font attributes.

# Msgs
The msgs section covers the implementation of message windows, including:
- Information
- Warning
- Error

# First Application Examples
1. **Menu Example**: Creating a simple 2-option menu.
2. **Menu 2 Levels Example**: Demonstrating nested menus.
3. **Form Example**: Includes all element types: label, field, checkbutton, listbutton, and button.

# Event Handling
This section delves into callbacks programming, including how to obtain data from components and use the action structure, which comprises error made and opToMade fields.