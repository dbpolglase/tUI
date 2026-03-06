---


---

<h1 id="introduction">Introduction</h1>
<p>The TUI project consists of three elements that allow you to create a powerful terminal user interface quickly, without needing any knowledge of the ncurses library it is built upon.</p>
<ul>
<li>The first element of the project is the <strong>libtui</strong> library, which provides a wrapper for the ncurses API. It allows interface creation by describing common elements for any interface: panels, buttons… and implements an engine to manage their actions.</li>
<li>The second element is a compiler (<strong>tbuild</strong>) that translates a user interface description in XML format into the necessary source files, which together with the libtui library, build the application.</li>
<li>The last element is a graphical application (<strong>tUI</strong>) built using the libtui library. Through it, you can construct your project’s interface visually, and it also serves as a demonstrator.</li>
</ul>
<h1 id="model">Model</h1>
<p>The project is based on a View model. Currently, three types of Views can be handled:</p>
<ul>
<li class="task-list-item"><input type="checkbox" class="task-list-item-checkbox" disabled=""> <strong>Panel</strong> View, which is essentially a canvas on which the following components or elements can be represented:
<ul>
<li><strong>Label</strong> element, for fixed texts in our interface.</li>
<li><strong>Button</strong> element, for application buttons.</li>
<li><strong>Check-button</strong> element, for check/toggle buttons.</li>
<li><strong>List-button</strong> element, for selection lists.</li>
<li><strong>Field</strong> element, for fields the user must fill in.</li>
</ul>
</li>
<li class="task-list-item"><input type="checkbox" class="task-list-item-checkbox" disabled=""> <strong>Table</strong> View, which allows representing data through tabulated lists.</li>
<li class="task-list-item"><input type="checkbox" class="task-list-item-checkbox" disabled=""> <strong>Edit</strong> View, which consists of a simple editor for handling files or plain text.</li>
</ul>
<h2 id="life-cycle">Life Cycle</h2>
<p>Views will have the following states:</p>
<ul>
<li><strong>Creation</strong>: Views are created at the start of the application according to their initial properties (size, color, …). Associated elements are also created if they exist.</li>
<li><strong>Show</strong>: Views are displayed at the time associated with the keyboard (or mouse) events indicated in the project tUI XML description.</li>
<li><strong>Activation</strong>: When the View or an element within it, if there are several, is activated it can take control of user events. The active element is shown in inverse video so the user perceives  it is active.</li>
<li><strong>Deactivation</strong>: When navigating from one element to another, the previously active element is deactivated before activating the next one.</li>
<li><strong>Hiding</strong>: When activating a new View, currently visible Views will be hidden according to a level management system, so any View with a level higher than the one to be activated will be hidden.Hiding a View does not erase the data entered.</li>
<li><strong>Destruction</strong>: In the case of destruction, besides hiding the View, all entered data will be erased.</li>
</ul>
<p>The life cycle therefore will be:<br>
<code>Create -&gt; Show -&gt; Activate -&gt; Deactivate -&gt; hide/destroy -&gt; Show -&gt; ...</code></p>
<h2 id="events">Events</h2>
<p>The active element will handle the input events that occur.</p>
<p>The following possible events associated with keyboard input are considered:</p>
<ul>
<li><strong>Enter</strong>, or enter. (Intro)</li>
<li><strong>Out</strong>, or exit. (Esc)</li>
<li><strong>Up</strong>, go up. (up arrow)</li>
<li><strong>Down</strong>, go down. (down arrow)</li>
<li><strong>Left</strong>, go left. (left arrow)</li>
<li><strong>Right</strong>, go right. (right arrow)</li>
<li><strong>Next</strong>, or next in the list. (TAB)</li>
<li><strong>Previous</strong>, or previous in the list. (SHIFT-TAB)</li>
<li><strong>Fn</strong>, or Function key. (F1-F12)</li>
</ul>
<p>When appropriate, the following events are handled internally (they are not configurable):<br>
<ul>    
<li>PgUp, page up</li>
    <li>PgDw, page down</li>
    <li> Init, go to the beginning</li>
    <li>End, go to the end</li>
    <li> Ins, change mode between insert and replace</li>
    <li>Backspace, delete backward</li>
    <li> Del, delete forward</li>
</ul></p>
<p>Additionally, if we allow mouse use:</p>
<ul>
<li>The <strong>left button</strong> will translate as:
<ul>
<li>If clicked on the active element, and if it is a component of a panel, into an “enter” event on it. If the View is a table, into selecting the record. If it is an edit View, into positioning the cursor at that location.</li>
<li>If clicked on another View and/or element among those shown, into navigating to it, i.e., activating that View/element.</li>
</ul>
</li>
<li>Clicking the <strong>right button</strong> will generally result in an “out” event.</li>
<li>The <strong>middle button</strong> will translate as Up/Down in table and edit Views.</li>
</ul>
<h1 id="general-aspects">General Aspects</h1>
<p>Below, some initial characteristics to consider before starting to create an application using tUI will be described. The easiest way is to explain the points described in the General section of the tUI graphical user interface, for which we start it with the command <code>tUI</code>.</p>
<p><img src="./doc/tui-1.jpg" alt="starting"></p>
<p>and create a new project with <code>Project-&gt;new</code>, fill out the form, and click on “Do it!”.<br>
If we then save the project (<code>Project-&gt;save</code>), we will see that a file with the project name and <code>.xml</code> extension has been generated.<br>
The content will look something like this:</p>
<pre><code>```xml
&lt;?xml version="1.0"?&gt;
&lt;TUI xmlns:tui="http://tui"&gt;
    &lt;Proyect&gt;
        &lt;Name&gt;firstProyect&lt;/Name&gt;
        &lt;Description&gt;First Proyect with tUI&lt;/Description&gt;
    &lt;/Proyect&gt;
&lt;/TUI&gt;
</code></pre>
<h2 id="properties">Properties</h2>
<p>The first step is to talk about the configuration or parameterization allowed by the project. (General-&gt;Properties)</p>
<p><img src="./doc/tui-2.jpg" alt="Properties"></p>
<h3 id="color">Color</h3>
<p>The application allows the use of color by applications, but not all terminals support or allow colors.<br>
For “normal” cases, this is not important; our application will simply be seen in black and white regardless of the colors used.<br>
In the XML file, the tag  will indicate that color use is allowed.<br>
In the visual tool tUI, we will check “Use Color” in the General-&gt;properties section.</p>
<h3 id="mouse">Mouse</h3>
<p>The application allows interaction via the mouse, but this can be counterproductive in certain cases.<br>
Similar to color, the  tag in the XML will indicate that the mouse is accepted, and its absence that it is not allowed.<br>
In the visual tool tUI, we will check “Use Mouse” in the General-&gt;properties section.</p>
<h3 id="errors">Errors</h3>
<p>The project uses the “error.c” module to manage detected errors.<br>
This module is initialized by calling:</p>
<pre><code>void ERR_printError(int print, char * file)
</code></pre>
<p>where we indicate whether to print errors and, if so, the file to write to.<br>
If we choose not to print errors, the programmer can use the methods:</p>
<p><code>int ERR_isError() and int ERR_lastError().</code></p>
<p>In the case of indicating that you want to print errors but not specifying a file (NULL), stdout will be used.</p>
<p>In our project’s XML file, this will be indicated with the tag:</p>
<p><code>&lt;Error&gt;errors.txt&lt;/Error&gt;,</code></p>
<p>which includes the file to write errors to.<br>
In the visual tool tUI, we will check “Print Errors” and indicate the file in the General-&gt;properties section.</p>
<h3 id="check-button">Check Button</h3>
<p>Check buttons work using three characters:</p>
<p>The character within a text that indicates the marking position/s.</p>
<p>The character to show when the element is not marked.</p>
<p>The character to show when the element is marked.</p>
<p>Although, as we will see, this can be changed in each check-button, this parameterization allows changing the default values ?, X, _ to, for example, ?, Y, N globally so it doesn’t have to be indicated in each check-button.<br>
In the XML, the same is achieved with the tag:</p>
<pre><code>xml
&lt;Check chCheck="63" chIsCheck="89" chNoCheck="78" /&gt;
&lt;!-- or --&gt;
&lt;Check chCheck="?" chIsCheck="Y" chNoCheck="N" /&gt;
</code></pre>
<p>In the visual tool tUI, we will indicate the appropriate characters “Ch. Check, Ch is Check, Ch is not Check” in the General-&gt;properties section.</p>
<h3 id="framing">Framing</h3>
<p>Views are displayed within a frame according to the given dimensions; these frames can be bordered.<br>
Borders are defined as border characters for top, bottom, left, right, and the four corners, typically dashes, bars, and the + symbol.<br>
For table and editor Views (others in the future) where scrolling can be performed, the scroll border description defined by the SBorder characters will be used instead of the Border ones.<br>
The characters configuring these borders are parameterizable in the application.</p>
<p>In the XML, it is possible to customize these borders with the tags:</p>
<pre><code>xml
&lt;Borders Up="45" Dw="45" Lf="124" Rg="124" Cul="43" Cur="43" Cdl="43" Cdr="43"/&gt;
&lt;SBorders Up="45" Dw="45" Lf="124" Rg="35" Cul="43" Cur="43" Cdl="94" Cdr="118"/&gt;
</code></pre>
<p>Where we indicate the characters that define it, either as a character or as a character code.<br>
In the visual tool tUI, we will indicate the appropriate characters for Border and SBorder in the General-&gt;properties section.</p>
<h3 id="user-main">User Main</h3>
<p>For necessary initializations associated with our application, it is possible to declare a user “main” function that will be called as the first program instruction.<br>
This function, analogous to the usual main, will receive as parameters the argc and argv with which the program was invoked.<br>
If the return obtained is different from 0, an exit of the program will proceed using this value as the exit code.<br>
This is declared in the General-&gt;properties section and will result in the following entry in the XML:</p>
<pre><code>&lt;Main&gt;userMain&lt;/Main&gt;
</code></pre>
<h3 id="user-end">User End</h3>
<p>As the last instruction of the program, the declared user-end function will be called, if it exists.<br>
It has no input parameters, and the output result will be used in the main’s return.<br>
This is declared in the General-&gt;properties section and will result in the following entry in the XML:</p>
<pre><code>&lt;End&gt;userEnd&lt;/End&gt;
</code></pre>
<h3 id="init-View">Init View</h3>
<p>As init-View, the View to activate at application startup should be indicated.<br>
The format will be:</p>
<pre><code>viewName:[elementName]
</code></pre>
<p>This is declared in the General-&gt;properties section and will result in the following entry in the XML:</p>
<pre><code>&lt;Init&gt;firstView:firstElement&lt;/Init&gt;
</code></pre>
<h3 id="summary">Summary</h3>
<p>The following XML file shows the result of having set the initial characteristics of our project:</p>
<pre><code>xml
&lt;?xml version="1.0"?&gt;
&lt;TUI xmlns:tui="http://tui"&gt;
    &lt;Proyect&gt;
        &lt;Name&gt;firstProyect&lt;/Name&gt;
        &lt;Description&gt;First Proyect with tUI&lt;/Description&gt;
        &lt;Main&gt;userMain&lt;/Main&gt;
        &lt;End&gt;userEnd&lt;/End&gt;
        &lt;Init&gt;firstView:firstElement&lt;/Init&gt;
        &lt;Properties&gt;
            &lt;Color/&gt;
            &lt;Mouse/&gt;
            &lt;Error&gt;errors.err&lt;/Error&gt;
            &lt;Check chCheck="63" chIsCheck="89" chNoCheck="78" /&gt;
            &lt;Borders Up="45" Dw="45" Lf="124" Rg="124" Cul="43" Cur="43" Cdl="43" Cdr="43"/&gt;
            &lt;SBorders Up="45" Dw="45" Lf="124" Rg="35" Cul="43" Cur="43" Cdl="94" Cdr="118"/&gt;
        &lt;/Properties&gt;
    &lt;/Proyect&gt;
&lt;/TUI&gt;
</code></pre>
<h2 id="keymap">Keymap</h2>
<p>A primary point of any terminal application is keyboard handling, and more specifically, the mapping of keys to events (i.e., which key code/s translate to an Enter event, for example).<br>
Traditionally, this is a source of problems when creating an application based on “ncurses” because, with high probability and depending on the terminal or its emulation, the associated termcap or terminfo is not configured according to our needs, and there may be keys that don’t work or work differently depending on the terminal used.<br>
The approach taken in the tUI library is to describe keyboard maps in which up to three key codes can be associated with an event.<br>
These keymaps reside in the header: mapKey.h and are designed for what we consider the most common case, i.e., a PC-type keyboard on an xterm emulation.<br>
However, this may not be correct in all cases, so it is possible to describe a custom keymap and indicate its use later in the elements that handle events instead of the keymaps defined in the application.<br>
In the XML file, we will indicate our custom keymaps as follows:</p>
<pre><code>xml
&lt;Keymaps&gt;
    &lt;Keymap Name="myKeymap"&gt;
        &lt;Enter ch1="10" ch2="343" ch3="0"/&gt;
        &lt;Out ch1="27" ch2="0" ch3="0"/&gt;
        &lt;Next ch1="9" ch2="0" ch3="0"/&gt;
        &lt;Previous ch1="353" ch2="0" ch3="0"/&gt;
        &lt;Up ch1="259" ch2="578" ch3="0"/&gt;
        &lt;Down ch1="258" ch2="581" ch3="0"/&gt;
        &lt;Left ch1="260" ch2="579" ch3="0"/&gt;
        &lt;Right ch1="261" ch2="580" ch3="0"/&gt;
        &lt;Fn/&gt;
    &lt;/Keymap&gt;
&lt;/Keymaps&gt;
</code></pre>
<blockquote>
<p>Code 0 indicates not necessary.</p>
</blockquote>
<p>And in the graphical interface, we will use the menu: General-&gt;Keymap-&gt;new and follow the associated instructions.</p>
<p><img src="./doc/tui-3.jpg" alt="Keymap"></p>
<blockquote>
<p>In the case of the Fn tag, we indicate that the entries for the<br>
definition of F0 to F11 from the ncurses library be entered</p>
</blockquote>
<p>.</p>
<h2 id="ed-functions">Ed Functions</h2>
<p>Text input elements of type “fields” must be associated with a validation or transformation function.<br>
The application has the following default validation functions by default:</p>
<ul>
<li><strong>numeric</strong>, accepts any character between 48 and 57, i.e., between 0 and 9</li>
<li><strong>alfnumeric</strong>, accepts characters between 48 and 57, 65-90 and 97-122,   i.e., 0-9, a-z and A-Z.</li>
<li><strong>alpha</strong>, accepts characters between 65-90 and 97-122, i.e., a-z and<br>
A-Z.</li>
<li><strong>7ascii</strong>, accepts characters between 32 and 126 (7-bit ASCII table).</li>
</ul>
<p>and the following transformation functions:</p>
<ul>
<li><strong>upper</strong>: is a toupper of the character.</li>
<li><strong>lower</strong>: is a tolower of the character.</li>
</ul>
<p>Additionally, these functions have two associated characteristics:</p>
<ul>
<li><strong>Alignment</strong>, right for the numeric function, left for the rest.</li>
<li><strong>Mode</strong>, insertion/replacement, in the default functions it is always replacement.</li>
</ul>
<p>If we need a specific custom function for a particular field, it can be defined as follows in the XML file:</p>
<p>In the XML file we write:</p>
<pre><code>xml
&lt;checksEdit&gt;
    &lt;checkEdit Name="OneTo9" Align="right" Mode="replace" /&gt;
&lt;/checksEdit&gt;
</code></pre>
<p>Where the value of Name will correspond to a user function of the form:</p>
<pre><code>int OneTo9(int * caracter)
</code></pre>
<p>Which:</p>
<p>Will receive the entered character as an input parameter.</p>
<p>Will return 0 if the character is valid, 1 otherwise.</p>
<p>Will modify the received character if required.</p>
<p>This user function will be invoked by the engine in the fields where its use is indicated.</p>
<p>In case it returns an invalid value, a beep will be emitted.</p>
<p>In the graphical interface, the same is done using the menu: General-&gt;Ed.Function.</p>
<p><img src="./doc/tui-4.jpg" alt="Ed.Function"></p>
<h2 id="colors">Colors</h2>
<p>All elements of the application can have a color associated with them. These colors are defined with three parameters:</p>
<ul>
<li>Background color</li>
<li>Text color</li>
<li>Font style to use</li>
</ul>
<p>The colors that can be managed are the basic colors handled by ncurses:</p>
<ol start="0">
<li>BLACK</li>
<li>BLUE</li>
<li>GREEN</li>
<li>CYAN</li>
<li>RED</li>
<li>MAGENTA</li>
<li>YELLOW</li>
<li>WHITE</li>
</ol>
<p>Likewise, the possible fonts are those accepted by ncurses:</p>
<ul>
<li>WA_NORMAL</li>
<li>WA_STANDOUT</li>
<li>WA_UNDERLINE</li>
<li>WA_REVERSE</li>
<li>WA_BLINK</li>
<li>WA_DIM</li>
<li>WA_BOLD</li>
<li>WA_ALTCHARSET</li>
<li>WA_INVIS</li>
<li>WA_PROTECT</li>
<li>WA_HORIZONTAL</li>
<li>WA_LEFT</li>
<li>WA_LOW</li>
<li>WA_RIGHT</li>
<li>WA_TOP</li>
<li>WA_VERTICAL</li>
<li>WA_ITALIC</li>
</ul>
<p>These colors or styles will be defined in the XML file:</p>
<pre><code>xml
&lt;Colors&gt;
    &lt;Color Name="myColor1" foreground="1" background="2" attr="WA_NORMAL"/&gt;
&lt;/Colors&gt;
</code></pre>
<p>And through the graphical application, we will use the form General-&gt;Colors-&gt;New</p>
<p><img src="./doc/tui-5.jpg" alt="Definición color"></p>
<p>For later use in the creation of elements.</p>
<p>It is possible to define an additional property to the font manually in the xml through the attr2 attribute, for example:</p>
<pre><code>&lt;Color Name="miColor1" foreground="1" background="2" attr="WA_BOLD" attr2="WA_UNDERLINE/&gt;
</code></pre>
<p>Some font types like ITALIC may not have any effect since they depend on the terminal, and others like WA_INVIS may have an effect on the color. For more details consult the ncurses documentation.</p>
<h2 id="msgs">MSGS</h2>
<p>The application contemplates the possibility of pop-up windows of three types:</p>
<ul>
<li>Information</li>
<li>Warning</li>
<li>Error</li>
</ul>
<p>The user will open these windows as appropriate in each circumstance programmatically. They will consist of a panel View with a title, centered on the screen or on the frame of the active View, in which the provided text will be displayed, in a certain style or color, and with 0 to 2 buttons also determined.</p>
<p>The application allows parameterizing these warning windows. To do this we can use the XML:</p>
<pre><code>xml
&lt;Colors&gt;
    &lt;Color Name="colorInfo" foreground="2" background="1" attr="WA_NORMAL"/&gt;
&lt;/Colors&gt;
&lt;Msgs&gt;
    &lt;Msg type="info" nroButtons="1"&gt;
        &lt;Title&gt;Information&lt;/Title&gt;
        &lt;Color&gt;colorInfo&lt;/Color&gt;
        &lt;Buttons&gt;
            &lt;Button1&gt;OK&lt;/Button1&gt;
        &lt;/Buttons&gt;
    &lt;/Msg&gt;
&lt;/Msgs&gt;
</code></pre>
<p>In this way, we change the message window of type information from a window with 0 buttons (default) to 1, we give it the title “Information”, change the color from noColor (default) to colorInfo, and set the button text to OK.</p>
<p>With the graphical application we will complete the form General-&gt;Msgs-&gt;Info</p>
<p><img src="./doc/tui-6.jpg" alt="Msgs Into"></p>
<p>In the case that the message window does not have any associated button, it will close after 5 seconds (modifiable value with MSG_setSegInfo) or through any keypress or mouse click.<br>
Message windows will remain as the only active ones, blocking the application until they are closed.</p>
<h1 id="first-application">FIRST APPLICATION</h1>
<p>We are now ready to create our first application. In this section, we will create several typical applications step by step as a visual way to document the project.</p>
<h2 id="menu">Menu</h2>
<p>As a first application, let’s create a simple menu with 2 options: OPTION A and OPTION B.</p>
<h3 id="project-creation">Project Creation</h3>
<p>We open the graphical interface and in <code>Project-&gt;New</code> we create a new project, for example, <code>application1</code>:<br>
<img src="./doc/menu1.jpg" alt="menu1"></p>
<h3 id="test-terminal">Test Terminal</h3>
<p>Next, we open another terminal on the machine we are using and get the associated tty. This data will be used in the <code>Project-&gt;T.TEST</code> option together with the type of terminal emulated:<br>
<img src="./doc/menu-2.jpg" alt="Term Test"></p>
<p>From this moment on, we can use this terminal to test what we are doing.</p>
<blockquote>
<p>It is advisable that the terminal we use does not accept input to avoid collision between sessions. The easiest way is to indicate a <code>sleep 9999999</code> in it.</p>
</blockquote>
<h3 id="color-1">Color</h3>
<p>As a first step, we choose a color for the menu, for which we fill out the <code>General-&gt;color</code> form and try combinations, for example, blue and black, green and red, with underline,…<br>
Using the Test button we can visualize the result in the terminal we have defined for testing and try different combinations until we find one that satisfies us.</p>
<blockquote>
<p>When indicating Test, a Clean notice will appear on the screen. By pressing OK the test screen will be cleared. If we indicate Cancel, the test will remain visible, allowing us to compare different combinations.</p>
</blockquote>
<p>Finally, we settle on a green background and a black foreground with a normal font type to which we give the name <code>colorMenu</code>.</p>
<h3 id="panel">Panel</h3>
<p>Let’s create the panel that will support our two-button menu:<br>
<code>View-&gt;Panel NEW</code><br>
and here we indicate:<br>
As ID: nothing, as this is an alternative way in which the user can refer to the view.<br>
As Name: <code>menu1</code>, this is mandatory and must be unique since all the internal mechanics of the application are done referencing this name (the alternative id is not used by the library).<br>
As Level: 1, any would work since we only have one level.<br>
As Title: nothing, as we do not want any.</p>
<blockquote>
<p>The title appears in the panel’s frame, so it will be necessary to indicate border if we want to give a title to the panel.</p>
</blockquote>
<p>As OP: <code>none</code>, this is the main panel and we do not need to hide or destroy.<br>
As Color: we will indicate <code>colorMenu</code> (navigate with the arrows and press enter to select).<br>
As Border: <code>N</code>, indicating we do not want a border.<br>
As Dimensions: We indicate for example 0,0 and 40,3.</p>
<blockquote>
<p>Positions and sizes will be relative to the screen with origin 0,0</p>
</blockquote>
<p><img src="./doc/menu3.jpg" alt="enter image description here"><br>
We click on DoIt!. The message “Done!” will be shown, and the new panel <code>menu1</code> will appear in the list of panels on the left.<br>
Then we click on TEST and if everything is fine, we will observe the panel we have described in the test terminal.</p>
<p>Now it’s time for you to play a little, change to border <code>Y</code> for example, save and test. (In this case, it is advisable to clean the test terminal after each test to avoid overlapping different tests).</p>
<blockquote>
<p>It is advisable to <strong>periodically save the project</strong> (<code>Project-&gt;save</code>) since the TEST is effectively executed with the library and certain errors (typically incorrect dimensions) can cause a catastrophic failure and close the application, losing the changes.</p>
</blockquote>
<h3 id="buttons">Buttons</h3>
<p>Let’s add the buttons to our menu:<br>
We click on the COMPONENTS button in the panel form, a new panel will open where we will select <code>new button</code> which will take us to the associated form, where we will proceed to create the button.</p>
<p>ID: none<br>
Name: <code>boton1</code><br>
Visible: <code>Y</code>, indicates that the element will be visible.</p>
<blockquote>
<p>The components or elements of a panel can be hidden. We can change this characteristic via programming.</p>
</blockquote>
<p>Select: <code>Y</code>, indicates that the element is selectable, meaning you can navigate to it either via mouse or keyboard.<br>
Color: we select <code>colorMenu</code>.<br>
Border: <code>Y</code><br>
Dimensions: 0,0 10,3</p>
<blockquote>
<p>Coordinates are relative to the panel, not to the screen.<br>
By indicating that we want a border, we must take into account that 2 lines and 2 columns are required to accommodate the border.</p>
</blockquote>
<p>Text: <code>OPTION A</code></p>
<p>We save with Do It! and check the result using the TEST button.</p>
<p>Without needing to exit, we modify the form:<br>
Name: <code>boton2</code><br>
Dimension: 12,0 10,3<br>
Text: <code>OPTION B</code><br>
<img src="./doc/menu4.jpg" alt="enter image description here"><br>
We save and check.</p>
<h3 id="moves">Moves</h3>
<p>Now let’s manage the menu dynamics.<br>
We go back (ESC) and again back (ESC) since the component list is not updated automatically, and we click again on COMPONENTS and select <code>boton1</code>.<br>
In the button form, we click on <strong>Moves</strong>.<br>
A screen opens with the possible events where we can indicate the movements (<code>view:element</code>) we want for these events.<br>
In this case, we will indicate that both the right and left arrow, as well as the next option (Next) and previous (Previous) take us to <code>boton2</code>.<br>
<img src="./doc/menuMove.jpg" alt="menuMove"></p>
<blockquote>
<p>Observe that we use relative referencing. When we do not indicate the view part, we are referring to the active view.<br>
That is, the notation <code>:boton1</code> is equivalent to <code>menu1:boton1</code>, but as we will see later, it is better to use the relative one, and not just for saving.</p>
</blockquote>
<p>We save the form and save again on the component form so that the component changes are saved.<br>
We go back (ESC) and select button 2 to indicate the “moves” of the button, which in this case will have <code>boton1</code> as the destination for the Next, Previous, left and right events.</p>
<p>Unfortunately, it is not possible to check the application’s dynamics without generating it, but first, let’s look at other points.</p>
<h3 id="exit">Exit</h3>
<p>To indicate the program exit, we will use the panel’s movement definitions for which we will use the <strong>Moves</strong> button on the panel form and, for example, on the Out event, we will indicate as the view <code>exit:</code>.</p>
<blockquote>
<p>When the event is not captured by the active component, the application will check if the event is captured by the active view and, if so, will proceed to execute what the view indicates.<br>
The view with the key name <code>exit</code> indicates to terminate the application.</p>
</blockquote>
<blockquote>
<p>Remember to save the modification in the panel, not only in the Move form.</p>
</blockquote>
<h3 id="check-the-application">Check the application</h3>
<p>Let’s proceed to check the built application, for this we press the button:<br>
<code>Make-&gt;Check</code><br>
If everything is correct, it will indicate the error that we do not have an initial view defined.<br>
Let’s go to <code>General-&gt;properties</code> and indicate as the initial view: <code>menu1:boton1</code>.<br>
If we repeat the check, everything should be fine now.</p>
<h3 id="edit">Edit</h3>
<p>Before continuing, let’s take a look at the xml generated when saving the project. To do this, click on <code>Edit-&gt;Open</code></p>
<pre><code>```xml
&lt;?xml version="1.0"?&gt;
&lt;TUI xmlns:tui="http://tui"&gt;
    &lt;Proyect&gt;
        &lt;Name&gt;Application1&lt;/Name&gt;
        &lt;Description&gt;my first tUI application&lt;/Description&gt;
        &lt;Main&gt;&lt;/Main&gt;
        &lt;End&gt;&lt;/End&gt;
        &lt;Init&gt;menu1:boton1&lt;/Init&gt;
        &lt;Properties&gt;
            &lt;Mouse/&gt;
            &lt;Color/&gt;
            &lt;Error&gt;errors.err&lt;/Error&gt;
            &lt;Borders Up="45" Dw="45" Lf="124" Rg="124" Cul="43" Cur="43" Cdl="43" Cdr="43"/&gt;
            &lt;SBorders Up="45" Dw="45" Lf="124" Rg="35" Cul="43" Cur="43" Cdl="94" Cdr="118"/&gt;
        &lt;/Properties&gt;
    &lt;/Proyect&gt;
    &lt;Colors&gt;
        &lt;Color Name="colorMenu" foreground="0" background="2" attr="WA_NORMAL"/&gt;
    &lt;/Colors&gt;
    &lt;Msgs&gt;
    &lt;/Msgs&gt;
    &lt;Panels&gt;
        &lt;Panel Id="0" Name="menu1" opToMade="none" Level="1"&gt;
            &lt;Color&gt;colorMenu&lt;/Color&gt;
            &lt;Dimension border="0" x="0" y="0" high="3" width="40"/&gt;
            &lt;FPanel /&gt;
            &lt;Move  out="exit:" /&gt;
            &lt;FAction /&gt;
        &lt;Components&gt;
        &lt;Component Id="0" Name="boton1" Type="button" &gt;
            &lt;Color&gt;colorMenu&lt;/Color&gt;
            &lt;Dimension border="1" x="0" y="0" high="3" width="10"/&gt;
            &lt;Text&gt;OPCION A&lt;/Text&gt;
            &lt;Move  next=":boton2"  previous=":boton2"  left=":boton2"  right=":boton2" /&gt;
            &lt;FAction /&gt;
            &lt;FComponent /&gt;
        &lt;/Component&gt;
        &lt;Component Id="0" Name="boton2" Type="button" &gt;
            &lt;Color&gt;colorMenu&lt;/Color&gt;
            &lt;Dimension border="1" x="12" y="0" high="3" width="10"/&gt;
            &lt;Text&gt;OPCION B&lt;/Text&gt;
            &lt;Move  next=":boton1"  previous=":boton1"  left=":boton1"  right=":boton1" /&gt;
            &lt;FAction /&gt;
            &lt;FComponent /&gt;
        &lt;/Component&gt;
        &lt;/Components&gt;
        &lt;/Panel&gt;
    &lt;/Panels&gt;
&lt;/TUI&gt;
</code></pre>
<p>This XML corresponds to our application1 project.</p>
<h3 id="compile-and-run">Compile and run</h3>
<p>Starting from the XML, the application will be generated, so as a previous step, we proceed to save the project (Project-&gt;save).<br>
From this XML and using the tbuild tool, the following are generated:</p>
<ul>
<li>projectName.c which constitutes the main of the built application.</li>
<li>projectName_func.h, with the prototypes of the callback functions we<br>
have defined.</li>
<li>projectName_func.c, with the skeleton of the callback functions to be<br>
implemented by the user.</li>
</ul>
<blockquote>
<p>The tbuild tool has options that allow avoiding the rewriting of<br>
prototypes or callback functions.</p>
</blockquote>
<p>Compiling the *.c files together with the tui library and the ncurses library, we will obtain our application.</p>
<p>Or we can use the supplied graphical interface, at least for these very simple projects.</p>
<ul>
<li>Copy the makefile_tui file located in /usr/include/tui to the working<br>
directory.</li>
<li>Execute Make-&gt;compile and respond OK to “Rewrite Functions File”<br>
since we have not generated it before.</li>
</ul>
<p>It proceeds to create a directory with the project name and compile it using this makefile (makefile_tui) which executes tbuild, compilation, and linking.<br>
<img src="./doc/compMenu.jpg" alt="enter image description here"></p>
<blockquote>
<p>Compilation and execution of projects from the graphical tool is done<br>
using this makefile (makefile_tui). Depending on the installation you<br>
have performed, you may need to adjust some data in it, such as the<br>
location of the tbuild tool or the location of libraries and headers.</p>
</blockquote>
<p>At this point, we can go to the created directory and execute the application manually or click on the Make-&gt;Execute button.<br>
If we do this (Make-Execute), your application will run on the test terminal and control will be ceded to it, meaning it will be fully operational, allowing us to check the movements.<br>
End the test application by triggering the Out event (ESC) and thus regain control to the graphical application to continue working.</p>
<h2 id="two-level-menu">Two-Level Menu</h2>
<p>To create a two-level menu, we will proceed by creating two panels similarly to how we did in the previous case, one that will contain the level 1 options and another with the level 2 options.<br>
To do this, we will use a feature of the graphical application.<br>
We go to View-&gt;Copy and select menu1. A form will open where we will indicate:<br>
To: nivel2<br>
Copy components: Y, the new View “nivel2” will also have two buttons, boton1 and boton2.</p>
<blockquote>
<p>Component names will not clash with each other if the first 4 letters<br>
of the panel differ.</p>
</blockquote>
<p>Copy moves: Y, we will later adjust it, especially if we have used absolute view:component references and not relative ones.<br>
Copy applications move: N<br>
Copy applications calls: N<br>
<img src="./doc/copy.jpg" alt="enter image description here"><br>
Now let’s make some modifications:<br>
We go to views-&gt;panels and select the panel nivel2. We change:<br>
Level: to level 2. (i.e., it is a submenu of the main menu).<br>
OP: to HIDE so that it is hidden when we return to the main level menu1.<br>
Dimension: to 0,4 40,3 so that it is displayed just below the previous one.</p>
<p>We also change the Moves of the panel nivel2 so that Out is no longer exit: but menu1:boton1. In this way, pressing ESC in any component of this level returns us to the main menu.</p>
<p>We save and check.</p>
<blockquote>
<p>To see how both panels would look, indicate no to “make clean” and<br>
execute the test of each one.</p>
</blockquote>
<p>The last adjustment we are going to make is to indicate that access to the submenu is done by pressing button1 of the menu. In the form of this button (menu1-boton1), clicking on Moves, we indicate for the Enter event nivel2:boton1.</p>
<blockquote>
<p>Here it is mandatory to use absolute reference since we are not<br>
talking about the active view.</p>
</blockquote>
<p>If we compile and execute the application, the result will be a two-level menu, the second of which opens when selecting Option A of the first level, and in which the second level is hidden when pressing “ESC”.</p>
<blockquote>
<p>Exercise: improve the appearance of the example, check the use of the mouse.</p>
</blockquote>
<p>In a similar way to this, we can define menus of any depth and complexity.</p>
<h2 id="form">Form</h2>
<p>Next, we are going to make a typical form in which we will put one element of each type.</p>
<h3 id="panel-1">Panel</h3>
<p>We start as always by creating a panel, with the following data, for example:</p>
<p>Name: form1<br>
Title: My first form<br>
Level: 2</p>
<blockquote>
<p>In this case, we are going to leave the main menu visible when opening the form, since only views with levels greater than 2 will be hidden.</p>
</blockquote>
<p>OP: DELE</p>
<blockquote>
<p>If we use HIDE, the entered data will persist between form openings. With DELE, they will be deleted when hiding it.</p>
</blockquote>
<p>Color: colorForm, a color that we should have previously created to our liking.<br>
Border: S. In this case, we are going to put a frame on the panel, and since we have given it a title, it is necessary to display it.<br>
Dimension: 5,5 and 60,15</p>
<p>We create it and test it to see if the canvas suits us.</p>
<h4 id="label">Label</h4>
<p>Let’s put a label inside it. To do this, we click on the COMPONENTS button and select NEW LABEL. The corresponding form will appear where we will enter the following data:</p>
<p>ID: none<br>
Name: ename<br>
Visible: Y, we want it to be shown.<br>
Select: N, labels are not selectable.</p>
<blockquote>
<p>It can be observed that this field is described as “non-selectable”, meaning we cannot access it to change the value.</p>
</blockquote>
<p>Color: colorForm. Any other created color can be used, but the result will be a bit odd.<br>
Border: N, we do not want a border on the label.<br>
Dimension: 2,2 20,1<br>
Text: NAME:</p>
<p>We save and test.</p>
<h4 id="field">Field</h4>
<p>Next, we are going to define the editable name field.<br>
To do this, we go back and select NEW FIELD and enter the data:</p>
<p>ID: 1, we are going to use the alternative reference.<br>
Name: name<br>
Visible: Y<br>
Select: Y,<br>
Color: colorForm<br>
Auto Enter: Y, auto enter forces an enter event at the moment the maximum size of the field is filled.<br>
Secret: N, fields marked as secret show * instead of the normal echo.<br>
Keymap: if we click on this button, it allows us to select among the user-defined keymaps. In our case, we do nothing since we will use the default.<br>
Ch. Ed: . is the character to show in the unfilled positions of the field. By default, they are ‘.’ which indicate the field size.<br>
Edit Functions: we are going to click on this text and select alpha as validation.</p>
<blockquote>
<p>This is an example list button with display OPEN.</p>
</blockquote>
<p>Border: N<br>
Dimension: 24,2 (next to the label) and 20,1 (field of 20 characters)<br>
Text: we do not indicate anything since we do not want a default value.</p>
<p>We save and test.</p>
<h4 id="check-button-1">Check Button</h4>
<p>Let’s define a check option next. To do this, we go back and select NEW CK. BUTTON and fill in:</p>
<p>ID: 2<br>
Name: check<br>
Visible: Y<br>
Select: Y<br>
Color: colorForm<br>
Border: N<br>
Dimension: 2,3 (below the previous field) and dimension 40, 1<br>
Text: This is a A-B check Button ?<br>
Check: N indicates whether it will be checked by default.<br>
Ch. Check: (empty) is the character to be substituted depending on whether it is checked or not. We will use the default (?).<br>
Ch. is Check: A when we check it, A will be shown.<br>
Ch is no Check: B when we uncheck it, B will be shown.</p>
<p>We save and check the result.</p>
<h4 id="list-button">List Button</h4>
<p>Let’s continue with the list button. First, we put a label for the list button:<br>
Select NEW LABEL and fill in:</p>
<p>ID: none<br>
Name: elist<br>
Visible: Y, we want it to be shown.<br>
Select: N, labels are not selectable.<br>
Color: colorForm, any other created color can be used but the result will be a bit odd.<br>
Border: N, we do not want a border on the label.<br>
Dimension: 2,4 20,1<br>
Text: GENDER:</p>
<p>We save, check, and exit to define the list button.<br>
Select NEW LIST BUTTON</p>
<p>ID: 3<br>
Name: gender<br>
Display: NORMAL,</p>
<blockquote>
<p>This is a list button with height 1. Activating it and pressing the<br>
up/down arrows, we can select among the following options:</p>
</blockquote>
<ul>
<li>
<blockquote>
<p>NORMAL,  visible and selectable.</p>
</blockquote>
</li>
<li>
<blockquote>
<p>HIDDEN hidden.</p>
</blockquote>
</li>
<li>
<blockquote>
<p>NOT SELECTABLE, not selectable</p>
</blockquote>
</li>
<li>
<blockquote>
<p>OPEN behaves like a dropdown list, the options are only visualized and<br>
can be selected by clicking on the button. It requires user<br>
programming to, once a value is selected, display it on screen.</p>
</blockquote>
</li>
</ul>
<p>Color: colorForm<br>
Keymap: default<br>
Border: Y<br>
Dimension: 24,4 and 12,5<br>
Text: We add the texts MALE, FEMALE and OTHER using the Add button.</p>
<p>To delete, we select from the list of added texts or write it directly and click on Del.</p>
<p>We save and proceed to verify the result.</p>
<h4 id="button">Button</h4>
<p>And now we only have one element left, which is the button that we have already seen with the menus, so we will simply add a button of the type:</p>
<p>Id:4<br>
Name: done<br>
Color: colorMenu<br>
Border: Y<br>
Dimension: 25,10 and 10,3<br>
Text: MADE</p>
<p>We save and proceed to verify the result.</p>
<h3 id="moves-1">Moves</h3>
<p>Let’s define the movements of the form:<br>
In the panel: Form1 we apply the movement "-1: " to the Out event (Panel Form -&gt; Moves). This will cause the ESC key anywhere in the form to return to the previous view.</p>
<blockquote>
<p>Movements of type -n indicate to the application to make “n” steps back in the path of views that ended in this view. In this way, a view can be invoked from different points and return naturally to them.</p>
</blockquote>
<p>In the View menu1 / boton2 we are going to apply in Moves form1:name for the Enter event, so that the form opens when clicking on boton2 of menu1.</p>
<p>In the form, we are going to apply the following movements:</p>
<p>In the element form1:name<br>
Enter, “:2” or :check</p>
<blockquote>
<p>This means that when we press Enter, the element with id=2 or the element with name=check will be activated.</p>
</blockquote>
<p>Next, “:2”<br>
Down, “:2”</p>
<blockquote>
<p>We will be able to navigate with the Tab key or with the Down key to the next element of the form.</p>
</blockquote>
<p>Previous, “:4”<br>
Up, “:4”</p>
<blockquote>
<p>With the SHIFT-TAB key or with the Up key we will go to the last element of the form, the button.</p>
</blockquote>
<p>Similarly for the check element we indicate:<br>
Enter, Next and Down, “:3”<br>
Previous, Up, “:1”</p>
<p>For the gender element, things change a bit. We indicate:<br>
Enter, Next, “:4”<br>
Previous, “:2”</p>
<blockquote>
<p>Observe that we do not indicate handling for the Up, Down events. In this case, up, down are used to navigate within the list of values of the list button, so if we handle them, it would be impossible to change between values.</p>
</blockquote>
<p>In the button element we indicate:<br>
Enter, -:</p>
<blockquote>
<p>-: is equivalent to -1:. That is, when pressing the button, exit or return to the menu.</p>
</blockquote>
<p>Next, down, :1<br>
Previous, up, :-3</p>
<p>Compile and test<br>
We save, compile, and test.<br>
The XML will have an appearance like this:</p>
<pre><code>xml
&lt;?xml version="1.0"?&gt;
&lt;TUI xmlns:tui="http://tui"&gt;
    &lt;Proyect&gt;
        &lt;Name&gt;Application1&lt;/Name&gt;
        &lt;Description&gt;My first tui Application&lt;/Description&gt;
        &lt;Main&gt;&lt;/Main&gt;
        &lt;End&gt;&lt;/End&gt;
        &lt;Init&gt;menu1:boton1&lt;/Init&gt;
        &lt;Properties&gt;
            &lt;Mouse/&gt;
            &lt;Color/&gt;
            &lt;Error&gt;errors.err&lt;/Error&gt;
            &lt;Borders Lf="124" Rg="124" Up="45" Dw="45" Cul="43" Cur="43" Cdl="43" Cdr="43"/&gt;
            &lt;SBorders Lf="124" Rg="35" Up="45" Dw="45" Cul="43" Cur="43" Cdl="94" Cdr="118"/&gt;
        &lt;/Properties&gt;
    &lt;/Proyect&gt;
    &lt;Colors&gt;
        &lt;Color Name="colorMenu" foreground="0" background="2" attr="WA_NORMAL"/&gt;
        &lt;Color Name="colorForm" foreground="3" background="1" attr="WA_NORMAL"/&gt;
    &lt;/Colors&gt;
    &lt;Msgs&gt;
    &lt;/Msgs&gt;
    &lt;Panels&gt;
        &lt;Panel Id="0" Name="menu1" opToMade="none" Level="1"&gt;
            &lt;Color&gt;colorMenu&lt;/Color&gt;
            &lt;Dimension border="0" x="0" y="0" high="3" width="40"/&gt;
            &lt;FPanel /&gt;
            &lt;Move  out="exit:" /&gt;
            &lt;FAction /&gt;
        &lt;Components&gt;
        &lt;Component Id="0" Name="boton2" Type="button" &gt;
            &lt;Color&gt;colorMenu&lt;/Color&gt;
            &lt;Dimension border="1" x="12" y="0" high="3" width="10"/&gt;
            &lt;Text&gt;OPTION B&lt;/Text&gt;
            &lt;Move  enter="form1:name"  next=":boton1"  previous=":boton1"  left=":boton1"  right=":boton1" /&gt;
            &lt;FAction /&gt;
            &lt;FComponent /&gt;
        &lt;/Component&gt;
        &lt;Component Id="0" Name="boton1" Type="button" &gt;
            &lt;Color&gt;colorMenu&lt;/Color&gt;
            &lt;Dimension border="1" x="0" y="0" high="3" width="10"/&gt;
            &lt;Text&gt;OPTION A&lt;/Text&gt;
            &lt;Move  enter="nivel2:boton1"  next=":boton2"  previous=":boton2"  left=":boton2"  right=":boton2" /&gt;
            &lt;FAction /&gt;
            &lt;FComponent /&gt;
        &lt;/Component&gt;
        &lt;/Components&gt;
        &lt;/Panel&gt;
        &lt;Panel Id="0" Name="nivel2" opToMade="hide" Level="2"&gt;
            &lt;Color&gt;colorMenu&lt;/Color&gt;
            &lt;Dimension border="0" x="0" y="4" high="3" width="40"/&gt;
            &lt;FPanel /&gt;
            &lt;Move  out="menu1:boton1" /&gt;
            &lt;FAction /&gt;
        &lt;Components&gt;
        &lt;Component Id="0" Name="boton2" Type="button" &gt;
            &lt;Color&gt;colorMenu&lt;/Color&gt;
            &lt;Dimension border="1" x="12" y="0" high="3" width="10"/&gt;
            &lt;Text&gt;OPTION B&lt;/Text&gt;
            &lt;Move  next=":boton1"  previous=":boton1"  left=":boton1"  right=":boton1" /&gt;
            &lt;FAction /&gt;
            &lt;FComponent /&gt;
        &lt;/Component&gt;
        &lt;Component Id="0" Name="boton1" Type="button" &gt;
            &lt;Color&gt;colorMenu&lt;/Color&gt;
            &lt;Dimension border="1" x="0" y="0" high="3" width="10"/&gt;
            &lt;Text&gt;OPTION A&lt;/Text&gt;
            &lt;Move  next=":boton2"  previous=":boton2"  left=":boton2"  right=":boton2" /&gt;
            &lt;FAction /&gt;
            &lt;FComponent /&gt;
        &lt;/Component&gt;
        &lt;/Components&gt;
        &lt;/Panel&gt;
        &lt;Panel Id="0" Name="form1" opToMade="destroy" Level="2"&gt;
        &lt;Title&gt;My first form&lt;/Title&gt;
            &lt;Color&gt;colorForm&lt;/Color&gt;
            &lt;Dimension border="1" x="5" y="5" high="15" width="60"/&gt;
            &lt;FPanel /&gt;
            &lt;Move  out="-1:" /&gt;
            &lt;FAction /&gt;
        &lt;Components&gt;
        &lt;Component Id="4" Name="done" Type="button" &gt;
                &lt;Color&gt;colorForm&lt;/Color&gt;
                &lt;Dimension border="1" x="25" y="10" high="3" width="10"/&gt;
                &lt;Text&gt;MADE&lt;/Text&gt;
                &lt;Move  enter="-:"  next=":1"  previous=":3"  up=":3"  down=":1" /&gt;
                &lt;FAction /&gt;
                &lt;FComponent /&gt;
        &lt;/Component&gt;
        &lt;Component Id="3" Name="gender" Type="lsbutton" &gt;
                &lt;Color&gt;colorForm&lt;/Color&gt;
                &lt;Dimension border="1" x="24" y="4" high="5" width="12"/&gt;
                &lt;Text&gt;MALE&lt;/Text&gt;
                &lt;Text&gt;FEMALE&lt;/Text&gt;
                &lt;Text&gt;OTHER&lt;/Text&gt;
                &lt;Move  enter=":4"  next=":4"  previous=":3" /&gt;
                &lt;FAction /&gt;
                &lt;FComponent /&gt;
        &lt;/Component&gt;
        &lt;Component Id="0" Name="elist" Type="label" &gt;
                &lt;Color&gt;colorForm&lt;/Color&gt;
                &lt;Dimension border="0" x="2" y="4" high="1" width="20"/&gt;
                &lt;Text&gt;GENDER:&lt;/Text&gt;
                &lt;Move /&gt;
                &lt;FAction /&gt;
                &lt;FComponent /&gt;
        &lt;/Component&gt;
        &lt;Component Id="2" Name="check" Type="ckbutton"  chIsCheck="A"  chNoCheck="B" &gt;
                &lt;Color&gt;colorForm&lt;/Color&gt;
                &lt;Dimension border="0" x="2" y="3" high="1" width="40"/&gt;
                &lt;Text&gt;This is a A-B check button, ?&lt;/Text&gt;
                &lt;Move  enter=":3"  next=":3"  previous=":1"  up=":1"  down=":3" /&gt;
                &lt;FAction /&gt;
                &lt;FComponent /&gt;
        &lt;/Component&gt;
        &lt;Component Id="1" Name="name" Type="field" &gt;
                &lt;Edit editType="alpha"  auto="y" /&gt;
                &lt;Color&gt;colorForm&lt;/Color&gt;
                &lt;Dimension border="0" x="24" y="2" high="1" width="20"/&gt;
                &lt;Move  enter=":2"  next=":2"  previous=":4"  up=":4"  down=":2" /&gt;
                &lt;FAction /&gt;
                &lt;FComponent /&gt;
        &lt;/Component&gt;
        &lt;Component Id="0" Name="ename" Type="label" &gt;
                &lt;Color&gt;colorForm&lt;/Color&gt;
                &lt;Dimension border="0" x="2" y="2" high="1" width="20"/&gt;
                &lt;Text&gt;NAME: &lt;/Text&gt;
                &lt;Move /&gt;
                &lt;FAction /&gt;
                &lt;FComponent /&gt;
        &lt;/Component&gt;
        &lt;/Components&gt;
        &lt;/Panel&gt;
    &lt;/Panels&gt;
&lt;/TUI&gt;
</code></pre>
<h3 id="handling-events">Handling Events</h3>
<p>Everything above is fine, we can create menus and forms, but something must be done with them.<br>
Let’s start with the most evident case: collecting data from the form and doing something.</p>
<p>To do this, we are going to do the following: go to the done button form and open the “App. Moves” section with the corresponding button.</p>
<p>Here we have a form where we can assign a callback to events. In this case, we assign to Enter: madeForm (for example).</p>
<p>We save and execute the “List-&gt;Calls” option. If we have done it well, an entry will appear for that component and the ENTER event, which will have the madeForm function assigned.</p>
<blockquote>
<p>List-&gt;Call is a table-type View. To navigate left/right, use the arrows.</p>
</blockquote>
<h4 id="prototype">Prototype</h4>
<p>Let’s compile and go to the Application1 directory. In the file Application_func.c we can see something like:</p>
<pre><code>c
trAction* madeForm (tComponent * component,int key){
static trAction action;
initAction(action);
return &amp;action;
}
</code></pre>
<p>This composes the prototype of the function that we must fill with our logic. It receives as parameters the keystroke that triggered the event and the component that captured it. This allows us, for example, to use the same function in different places of our interface.</p>
<h4 id="programming-data-retrieval">Programming, Data Retrieval</h4>
<p>Let’s start with data retrieval. For this, there are two key functions:</p>
<pre><code>void * LVIEW_getElement(char * nView, char * nComponent);
</code></pre>
<p>that allows us to obtain the reference to any element of any View, using either the id or the name.<br>
If we indicate NULL as nView, we will refer to the active View.</p>
<p>and</p>
<pre><code>char * COMPONENT_getValue(tComponent * component);
</code></pre>
<p>that allows us to obtain the current value of the component. In the case of checkButton components, the value NULL will indicate not checked and !=NULL checked.</p>
<p>In our simple example:</p>
<pre><code>c
char * nameValue = COMPONENT_getValue(LVIEW_getElement(NULL,"name"));
</code></pre>
<p>Will obtain the value of the name entered in the name field.</p>
<pre><code>c
int checkValue = COMPONENT_getValue(LVIEW_getElement(NULL,"check"))==NULL?0:1;
</code></pre>
<p>Will obtain the value of the check (checked or not).</p>
<pre><code>c
char * genderValue = COMPONENT_getValue(LVIEW_getElement(NULL,"gender"));
Will obtain the selected text.

c
int lineSelect;
char * genderValue = COMPONENT_getSelectValue(LVIEW_getElement(NULL,"gender"),&amp;lineSelect);
</code></pre>
<p>Will obtain the text and the selected line.</p>
<h4 id="example">Example</h4>
<p>Let’s obtain the data and write them to a file. We modify the Application1_func.c file in the Application1 directory and write:</p>
<pre><code>c
trAction* madeForm (tComponent * component,int key){
static trAction action;
int lineSelect;
char * nameValue;
int checkValue;
char * genderValue;
FILE * fd;

 initAction(action);

  fd = fopen("/tmp/tuiApplication","w");
  nameValue = COMPONENT_getValue(LVIEW_getElement(NULL,"name"));
  checkValue = COMPONENT_getValue(LVIEW_getElement(NULL,"check"))==NULL?0:1;
  genderValue = COMPONENT_getValue(LVIEW_getElement(NULL,"gender"));
  genderValue = COMPONENT_getSelectValue(LVIEW_getElement(NULL,"gender"),&amp;lineSelect);
  fprintf(fd,"name: %s\n checkValue: %d\n, genderValue: %s \n, genderLine: %d\n",
nameValue,checkValue,genderValue,lineSelect);
  fclose(fd);

return &amp;action;
}
</code></pre>
<p><strong>We proceed to compile but now we must indicate CANCEL to “Rewrite Functions File” or we will lose these changes.</strong></p>
<blockquote>
<p>Observe that the effect is that we compile without the -p when executing tbuild.</p>
</blockquote>
<p>Now, when executing the application, the values entered in the form will be written to the file /tmp/tuiApplication.</p>
<h4 id="improving">Improving</h4>
<p>We haven’t done any error control. Let’s introduce some, for example if fopen fails.</p>
<pre><code>c
char * file="/tmp/tuiApplication";
 initAction(action);

 FILE * fd;

  fd = fopen(file,"w");
  if (fd == NULL){
    MSG_create(M_ERROR,CENTER_VIEW,"Unable to Open %s file",file);
  }
</code></pre>
<p>In this way, we force the opening of an MSG View of type ERROR, centered on the form View, with the indicated text.</p>
<h4 id="redirecting">Redirecting</h4>
<p>This is fine, but it does not prevent the event handling logic from continuing. To change that, we will make use of the action.<br>
The action structure consists of 3 fields: error, made and opToMade, and is returned as the result of the call.</p>
<h5 id="action.error">action.error</h5>
<p>The error field has values 0 or 1. If error=1 is returned, any subsequent processing of the event is canceled. For example, in our case:</p>
<pre><code>c
fd = fopen(file,"w");
if (fd == NULL){
    MSG_create(M_ERROR,CENTER_VIEW,"Unable to Open %s file",file);
    action.error=1;
    return &amp;action;
}
</code></pre>
<p>Will cause the tool to no longer consider valid subsequent treatments of the event, in this case the order to return to the previous View.</p>
<h5 id="action.made">action.made</h5>
<p>The made field can have values 0 or 1. The value 1 indicates that the event is handled by the user and should not be handled by the application.</p>
<h6 id="action-optomade-and-componentnext">action opToMade and componentNext</h6>
<p>In cases where the event is handled by the application, we must indicate the treatment to perform. This is done with the componentNext field, which will be a string of the type view:element with the next view and/or component to show, and opToMade, which will indicate what to do with the current View: NONE, HIDE, DESTROY… values defined in enum Ops.</p>
<pre><code>c
if (fd == NULL){
    MSG_create(M_ERROR,CENTER_VIEW,"Unable to Open %s file",file);
    action.made=1;
    action.opToMade=OP_HIDE;
    action.componentNext="nivel2:boton1";
    return &amp;action;
}
</code></pre>
<p>In this case, we say that in case of error, go to the nivel2 View of the menu.</p>
<h4 id="improving-more">Improving more</h4>
<p>Another thing we can do is obtain the value of the MSG and act accordingly. For example:</p>
<pre><code>c
if (fd == NULL){
    if (MSG_create(M_WARNING,CENTER_VIEW,"Unable to Open %s file\n goto nivel2 ?",file) ==0)
    {
      action.made=1;
      action.opToMade=OP_HIDE;
      action.componentNext="nivel2:boton1";
    }
    else
      action.error=1;
    return &amp;action;
}
</code></pre>
<p>We have changed the MSG to type WARNING, which has 2 buttons (by default) OK, CANCEL, and if the user presses the first one (button 0, OK), we go to the nivel2 View; otherwise, we simply say error and continue in the View.</p>
<h4 id="function-keys">Function Keys</h4>
<p>Function key events can be captured in a similar way. The only difference is that the callback will be generic to all of them.</p>
<p>It will receive as an additional parameter the Fn pressed (0-11), and it will be the programming that indicates which one is handled and which one is not.</p>
<pre><code>c
trAction* fnKey (tComponent * component,int key,int Fn){
static trAction action;
 initAction(action);
return &amp;action;
}
</code></pre>
<p>XML<br>
Let’s take a look at the XML generated with these callback functions:</p>
<pre><code>xml
&lt;Component Id="4" Name="done" Type="button" &gt;
        &lt;Color&gt;colorMenu&lt;/Color&gt;
        &lt;Dimension border="1" x="25" y="10" high="3" width="10"/&gt;
        &lt;Text&gt;MADE&lt;/Text&gt;
        &lt;Move  enter="-:"  next=":1"  previous=":3"  up=":3"  down=":1" /&gt;
        &lt;FAction   enter="madeForm"  Fn="fnKey" /&gt;
        &lt;FComponent /&gt;
</code></pre>
<h4 id="programming-data-loading">Programming, Data Loading</h4>
<p>In any form, it is common to have to load data; some will be default and others not.<br>
In the case of default values, we have already seen how to do it: simply use the Text tag in the XML, and the component will be filled with that data.<br>
For the rest of the cases, we will make use of the life cycle callbacks.<br>
For example, in this case, we will make a function execute before showing the View, where we will load the data.<br>
Open the form1 View form and click on the button: “App. Functions” and indicate in the “PRE Show” field the value loadForm1 and save.</p>
<blockquote>
<p>It is possible to introduce a user function at each point of the life cycle (create, show, activate, deactivate, hide, destroy) of the Views, either prior to its execution or as a subsequent step.</p>
</blockquote>
<p>In the View List-&gt;Calls, the new defined function should appear.</p>
<h4 id="prototype-1">prototype</h4>
<p>If we compile again indicating “Rewrite application functions” (i.e., with -p in tbuild), we will be able to observe in the functions file the prototyping of the callback to be filled.</p>
<p>For now, it is better to continue indicating NO to “Rewrite applications functions” so as not to lose previous changes.</p>
<pre><code>c
void loadForm1(tPanel * panel){
return;
}
</code></pre>
<p>The prototype of the function is this, in which we receive as a parameter the panel View that triggered it.</p>
<p>example<br>
Let’s fill the loadForm1 function:</p>
<pre><code>c
void loadForm1(tPanel * panel){
  COMPONENT_setValue(LVIEW_getElement("form1","name"),"Smith");
  COMPONENT_setValue(LVIEW_getElement("form1","check"),NULL);
  COMPONENT_addText(LVIEW_getElement("form1","gender"),"XX");
  COMPONENT_setSelectValue(LVIEW_getElement("form1","gender"),2,NULL);
  COMPONENT_setText(LVIEW_getElement("form1","done"),"Do");
 return;
}
</code></pre>
<p>With this, when opening the form, the name “smith” will appear, the check will be unchecked, we will have added the value “XX” to the select and selected value 2 of the list (we could also have put -1,“OTHER”), and we have changed the button text to “Do”.</p>
<p>You can copy that code to the source functions, compile and test.<br>
<img src="./doc/form.jpg" alt="enter image description here"></p>
<blockquote>
<p>We could navigate over the panel parameter received and make changes as we will see in the programming section, but it is better to use the API that we will see.</p>
<p>Observe that in this case we specify the View when calling LVIEW because the View we are manipulating is not the active one.</p>
</blockquote>
<h4 id="xml">XML</h4>
<p>Observe that in the XML we now have an entry for FPanel.</p>
<pre><code>xml
    &lt;Panel Id="0" Name="form1" opToMade="destroy" Level="2"&gt;
    &lt;Title&gt;Mi first form&lt;/Title&gt;
            &lt;Color&gt;colorMenu&lt;/Color&gt;
            &lt;Dimension border="1" x="5" y="5" high="15" width="60"/&gt;
            &lt;FPanel  preShow="loadForm1" /&gt;
            &lt;Move  out="-:" /&gt;
            &lt;FAction /&gt;
    &lt;Components&gt;
</code></pre>
<h2 id="tables">TABLES</h2>
<p>Let’s now create some tables to visualize data. Let’s define one: View-&gt;table NEW</p>
<p>Definition<br>
Id: none,<br>
Level: 3</p>
<blockquote>
<p>Again, we are going to leave all previous panels visible. You can change this by playing with the level.</p>
</blockquote>
<p>Name: table1<br>
Title: Personal Data<br>
Op: DELETE<br>
Columns: Len:23,NAME (Add)<br>
Len:15,GENDER (Add)<br>
Border: Y<br>
Dimension: 20,6 and 40,10<br>
Head C: colorCabecera<br>
Data Color: colorBody<br>
Show Head: Y, show a table header.<br>
Keymap: default<br>
Vtl Line: Y, include a line between record and record.<br>
Hz. Line: Y, separate the fields of the records with a horizontal line.</p>
<p>We apply and test.<br>
We will observe that only the first column is seen and … in the header; the frame size is not sufficient to accommodate both columns. You can make it a bit larger, for example 42 instead of 40, leave it as is and have navigation done with the arrows, remove the vertical separator lines, or remove the border.<br>
In our case, we put 42 and that’s it.</p>
<h3 id="moves-2">Moves</h3>
<p>We add the following movement Out: -1. to go back.<br>
And in the panel nivel2-boton1 App. Moves: Enter=table1: to open it.</p>
<p>compile and test.<br>
The xml will now have this addition:</p>
<pre><code>xml
&lt;Tables&gt;
    &lt;Table Id="0" Name="table1" opToMade="destroy" Level="3"&gt;
    &lt;Title&gt;Datos&lt;/Title&gt;
    &lt;Dimension border="1" x="20" y="6" high="10" width="42"/&gt;
    &lt;Style head="1"  hLine="1"  vLine="1"  colorHead="colorMenu"  colorData="colorMenu"  /&gt;
    &lt;Elements&gt;
        &lt;Element size="23"&gt;NAME                &lt;/Element&gt;
        &lt;Element size="15"&gt;GENDER              &lt;/Element&gt;
    &lt;/Elements&gt;
    &lt;FTable /&gt;
    &lt;Move  out="-1:" /&gt;
    &lt;FAction /&gt;
    &lt;/Table&gt;
&lt;/Tables&gt;
</code></pre>
<p>And if we compile and test, an empty table should appear when pressing button1 of the level2 submenu of our menu:</p>
<h3 id="load-data">load data</h3>
<p>Well, let’s fill it with data. For this, we define a callback in the preShow of the table, for example loadTable, similarly to how we did in the panel (in App. Func of the form we put that data, save, verify that there is a new function in List-&gt;Func and proceed to check).<br>
The resulting XML will have added:</p>
<pre><code>xml
&lt;Tables&gt;
    &lt;Table Id="0" Name="table1" opToMade="destroy" Level="3"&gt;
    &lt;Title&gt;Datos&lt;/Title&gt;
    &lt;Dimension border="1" x="20" y="6" high="10" width="42"/&gt;
    &lt;Style head="1"  hLine="1"  vLine="1"  colorHead="colorMenu"  colorData="colorMenu"  /&gt;
    &lt;Elements&gt;
        &lt;Element size="23"&gt;NAME                &lt;/Element&gt;
        &lt;Element size="15"&gt;GENDER              &lt;/Element&gt;
    &lt;/Elements&gt;
    &lt;FTable  preShow="loadTable" /&gt;
    &lt;Move  out="-1:" /&gt;
    &lt;FAction /&gt;
    &lt;/Table&gt;
&lt;/Tables&gt;
</code></pre>
<p>And if we force the recreation of the functions file, we will have:</p>
<pre><code>c
void loadTable(tTable * table){
return;
}
</code></pre>
<p>Observe that now we have the table View as a parameter.</p>
<h3 id="text-class">TEXT class</h3>
<p>All elements that are part of the interface have an associated text structure to support data.<br>
This structure consists of an array of arrays of lines and fields, i.e., a three-dimensional array.<br>
So far, we have performed data manipulations using specific functions from the component API, and this is because the structure and function of these components recommend this type of manipulation.<br>
In the case of table and edit Views, however, it is more convenient to make direct use of this class and its associated structure since understanding it may be necessary.</p>
<h3 id="method-1-of-loading">Method 1 of loading:</h3>
<p>We load the table data by data:</p>
<pre><code>c
void loadTable(tTable * table){
 int i;
 char data[21];

  for (i=0;i!=4;i++){
    sprintf(data,"data%d",i);
    TEXT_addData(table-&gt;text,data);
  }

return;
}
</code></pre>
<h3 id="method-2">Method 2</h3>
<p>Line by line:</p>
<pre><code>c
void loadTable(tTable * table){
 int i;
 char data[21];
 char * dataLine[4][2]={{"l1dato1","l1dato2"},
                        {"l2dato1","l2dato2"},
                        {"l3dato1","l3dato2"},
                        {"l4dato1","l4dato2"}} ;
 /* by simple data. /
  for (i=0;i!=4;i++){
   sprintf(data,"data%d",i);
   TEXT_addData(table-&gt;text,data);
  }

 /* by register */
 for (i=0;i!=4;i++)
   TEXT_addLine(table-&gt;text,2,dataLine[i]);


 return;
}
</code></pre>
<h3 id="method-3">Method 3</h3>
<p>From a file using a separator between fields:</p>
<pre><code>c
int TEXT_loadTableFile(tText * miText,char  * fileName,char separator);
</code></pre>
<h3 id="obtaining-data">Obtaining data</h3>
<p>Good, we already have data and we can move up and down between them. The next part remains: how to know what data the user has selected.<br>
For this, we will act similarly to how we have done before. We will go to the table form and select the “App. Moves” button of it and associate the function selTable to the Enter event.</p>
<p>We add the following code to our callback function:</p>
<pre><code>c
trAction* selTable (tTable * table,int key){
static trAction action;
 initAction(action);

 MSG_create(M_INFO,CENTER_TERMINAL,"El dato es %s y %s\n",
 TABLE_getColumnValue(table,0),
 TABLE_getColumnValue(table,1));

return &amp;action;
}
</code></pre>
<p>We compile and test. Now, by pressing enter on a row or double-clicking with the mouse, an information window will appear with the data of the active line.</p>
<p><img src="./doc/Table.jpg" alt="enter image description here"></p>
<blockquote>
<p>You can also export the complete table to a file via<br>
int TEXT_saveTabFile(tText * miText, char * fileName, char separator);</p>
</blockquote>
<h3 id="practice">Practice</h3>
<p>We leave as practice filling the table with the data entered in the form when giving OK.</p>
<blockquote>
<p>Hint: (tTable *)LVIEW_getElement(“table1”,NULL);</p>
</blockquote>
<p>We also leave as practice trying the difference between OP_HIDE and OP_DELETE.</p>
<h2 id="edit-1">EDIT</h2>
<p>Let’s now create an editing View, EDIT. For this, View-&gt;edit NEW</p>
<p>Definition<br>
Id: none,<br>
Name: View<br>
Level: 3<br>
Title: View of file Xml<br>
Op: DELETE<br>
Read Only: Y<br>
File: Application1.xml<br>
Border: Y<br>
Dimension: 0,0 and 80,24</p>
<blockquote>
<p>In this case, the menus will be hidden because we occupy the entire screen.</p>
</blockquote>
<p>Color: colorEditor<br>
Keymap: default</p>
<p>We apply and test.<br>
With this, we have a frame that will typically occupy the entire terminal.</p>
<h3 id="moves-3">Moves</h3>
<p>In the View we have created, we apply as move Fn: 1 -:, meaning that the F1 function key goes back to the previous screen.<br>
In the panel nivel2, boton2, we apply as enter View:, meaning that it opens this View.<br>
We save and check.</p>
<h3 id="xml-1">xml</h3>
<pre><code>xml
&lt;Edits&gt;
    &lt;Edit Name="view" opToMade="destroy" Level="3" Id="0"  ReadOnly="s"  &gt;
    &lt;Title&gt;View of file Xml&lt;/Title&gt;
    &lt;Dimension border="1" x="0" y="0" high="24" width="80"/&gt;
    &lt;Color&gt;colorView&lt;/Color&gt;
        &lt;File&gt;Application1.xml&lt;/File&gt;
    &lt;FEdit /&gt;
    &lt;Move  F1="-:" /&gt;
    &lt;FAction /&gt;
    &lt;/Edit&gt;
&lt;/Edits&gt;
</code></pre>
<p>In the xml, the Edits entry and a new Edit entry with the data we indicated have been created.</p>
<h3 id="compilation">Compilation</h3>
<p>So we save, compile, and execute. We will see that now, when clicking on button 2 of the level 2 submenu, a View of the application’s XML file is shown, in which we can move with the keyboard or mouse.<br>
Pressing F1 will return us to the previous menu.<br>
<img src="./doc/Edit.jpg" alt="enter image description here"></p>
<h3 id="data-loading">Data Loading</h3>
<p>In this case, we have forced the loading of a file in the View definition itself, but this will not be the usual case.<br>
The usual will be that the file to load is something dynamic. How is this done?<br>
We remove the File entry from the Edit View definition.<br>
We introduce a new callback in the preShow of the Edit View, for example loadFile (App. Functions).</p>
<pre><code>c
void loadFile(tEdit * edit);
</code></pre>
<p>We will have to fill the loadFile function, which receives the associated View as a parameter.</p>
<pre><code>c
void loadFile(tEdit * edit)
{
 int maxLineSize=200;
 int linesBlockRead=50;

  EDIT_loadFile(edit,"Application1.xml",maxLineSize,linesBlockRead);
}
</code></pre>
<p>The differences with the previous one are as follows: in the first case, when we indicate it with the XML tag, the file will be loaded immediately after creating the component and never again, so it will constitute a static View of the file.<br>
In addition, the file loading parameters, buffer reading size or maxLineSize and block of number of lines to create, are fixed via defines in the application_func.h file according to the size given to the window.</p>
<h3 id="dynamic-data-loading">Dynamic Data Loading</h3>
<p>The edit View can also be used more dynamically, i.e., to include data that does not come from a file. For this, we use the TEXT class methods at a low level.</p>
<pre><code>c
void loadFile(tEdit * edit)
{
 int nroInitColumns=100;
 int nroInitLines=50;
 int nroInitFields=1;

 edit-&gt;text = TEXT_newEdit(nroInitColumns,nroInitLines,nroInitFields);
 TEXT_addEditData(edit-&gt;text,"Linea1");
 TEXT_addEditData(edit-&gt;text,"Linea2");
 TEXT_addEditData(edit-&gt;text,"Linea3");
}
</code></pre>
<p>The TEXT class is the support for the data of Views and components. It is divided into lines, fields, and field sizes.<br>
These can be more or less dynamic depending on where we use them. In the case of a field, for example, the size is fixed by the component size. In the case of the edit View, these are dynamic based on the size of the lines read.</p>
<h3 id="practice-1">Practice</h3>
<p>We leave as practice filling the View view with the data entered in the form when giving OK.</p>
<blockquote>
<p>Hint: (tEdit*)LVIEW_getElement(“view”,NULL);</p>
</blockquote>
<p>We also leave as practice trying the difference between OP_HIDE and OP_DELETE.<br>
We also leave as practice to program, for example, F2 to save the file (first removing the readOnly, of course).</p>
<h2 id="summary-1">Summary</h2>
<p>Although we have not seen in detail all the possibilities (such as making adaptive menus or dynamic forms playing with the component’s display characteristic, the use of refresh to reflect changes immediately, how to change the event map, or how to pass information between different callbacks…), what has been seen so far covers practically most scenarios.</p>
<p>For the rest, the graphical application itself serves as an example since all scenarios have been attempted to be reflected and tested in it, although this resulted in a somewhat strange or non-homogeneous interface.</p>
<blockquote>
<p>It is advisable to take a look at the programming section to understand a bit the structure of the project and how to perform certain tasks such as passing data between callbacks, changing elements and the information they contain dynamically.</p>
</blockquote>
<h1 id="tui-xml">TUI XML</h1>
<p>Well, with this we now have a vision of how to make practically any type of application.<br>
The key, as observed, is the XML that describes your application, a file that you can edit by hand or via the graphical interface, and that once compiled will produce the application.<br>
A file <code>tui.xsd</code> that defines the valid structure of this XML is included, but we will describe it here quickly:</p>
<pre><code>xml
&lt;?xml version="1.0"?&gt;
&lt;TUI xmlns:tui="http://tui"&gt;
.......
&lt;/TUI&gt;
</code></pre>
<h2 id="project-section">Project Section</h2>
<p>The XML file will contain a descriptive section of the project and the general properties.</p>
<pre><code>xml
&lt;Proyect&gt;
    &lt;Name&gt;name of Proyect&lt;/Name&gt;
    &lt;Description&gt;description&lt;/Description&gt;
    &lt;Main&gt;your Main if any&lt;/Main&gt;
    &lt;End&gt;your End if any&lt;/End&gt;
    &lt;Init&gt;initView:[initElement]&lt;/Init&gt;
    &lt;Properties&gt;
        &lt;Mouse/&gt; (if mouse)
        &lt;Color/&gt; (if color)
        &lt;Error&gt;File of error&lt;/Error&gt; (if write)
        &lt;Check chCheck="63" chIsCheck="89" chNoCheck="N" /&gt; (optional, if not default, valid number or character code).
        &lt;Borders Up="45" Dw="45" Lf="a" Rg="124" Cul="b" Cur="43" Cdl="43" Cdr="43"/&gt; (if not default, valid number or character code)
        &lt;SBorders Up="45" Dw="x" Lf="y" Rg="35" Cul="43" Cur="43" Cdl="94" Cdr="118"/&gt; (if not default valid number or character code)
    &lt;/Properties&gt;
&lt;/Proyect&gt;
</code></pre>
<h2 id="colors-section">Colors Section:</h2>
<p>If the application uses colors/fonts, a colors section will be created with their definition.</p>
<pre><code>xml
&lt;Colors&gt; (optional)
    &lt;Color Name="name of Color" foreground="[0-8]" background="[0-8]" attr="WA_*" attr2="WA_*"/&gt; (0-*)
&lt;/Colors&gt;
</code></pre>
<h2 id="check-edit-section">Check Edit Section:</h2>
<p>Validations for component field texts defined by the user will be defined via entries in the checksEdit section.</p>
<pre><code>xml
&lt;checksEdit&gt;(optional)
    &lt;checkEdit Name="name of Check" Align="right|left" Mode="replace|insert" /&gt;(0-*)
&lt;/checksEdit&gt;
</code></pre>
<h2 id="keymap-section">Keymap Section</h2>
<p>If it is necessary to use custom keymaps, they will be defined in the Keymaps section.</p>
<pre><code>xml
&lt;Keymaps&gt; (optional)
    &lt;Keymap Name="name Of Keymap"&gt; (0-*)
        &lt;Enter ch1="10" ch2="0" ch3="0"/&gt; (optional, valid number or character 0 not applicable).
        &lt;Out ch1="27" ch2="0" ch3="0"/&gt; (optional, valid number or character 0 not applicable).
        &lt;Next ch1="9" ch2="0" ch3="0"/&gt; (optional, valid number or character 0 not applicable).
        &lt;Previous ch1="353" ch2="0" ch3="0"/&gt; (optional, valid number or character 0 not applicable).
        &lt;Up ch1="259" ch2="0" ch3="0"/&gt; (optional, valid number or character 0 not applicable).
        &lt;Down ch1="258" ch2="0" ch3="0"/&gt; (optional, valid number or character 0 not applicable).
        &lt;Left ch1="260" ch2="0" ch3="0"/&gt; (optional, valid number or character 0 not applicable).
        &lt;Right ch1="261" ch2="0" ch3="0"/&gt; (optional, valid number or character 0 not applicable).
        &lt;Fn/&gt; (optional, captures Function keys).
    &lt;/Keymap&gt;
&lt;/Keymaps&gt;
</code></pre>
<h2 id="msgs-section">Msgs Section</h2>
<p>If you want to modify the structure of the warning windows, they will be redefined via the Msgs section.</p>
<pre><code>xml
&lt;Msgs&gt; (optional, if not default).
    &lt;Msg type="info|warning|error" nroButtons="0|1|2"&gt; (optional)
        &lt;Title&gt;titulo&lt;/Title&gt; (optional)
        &lt;Color&gt;color&lt;/Color&gt; (optional)
        &lt;Buttons&gt;
            &lt;Button1&gt;texto boton1&lt;/Button1&gt; (optional)
            &lt;Button2&gt;texto boton2&lt;/Button2&gt; (optional)
        &lt;/Buttons&gt;
    &lt;/Msg&gt;
&lt;/Msgs&gt;
</code></pre>
<h2 id="panels-section">Panels Section</h2>
<p>If the application requires panels, they will be defined in the Panels section.</p>
<pre><code>xml
&lt;Panels&gt; (optional)
    &lt;Panel Id="0 or Id. panel" Name="name of Panel" opToMade="none|hide|destroy" Level="level of Panel"&gt; (0-*)
        &lt;Title&gt;Titulo&lt;/Title&gt; (optional)
        &lt;Color&gt;color Panel&lt;/Color&gt; (optional)
        &lt;Dimension border="0|1" x="0" y="0" high="24" width="80"/&gt;
        &lt;Keymap&gt;own keymap&lt;/Keymap&gt; (optional)
        &lt;Components&gt; (0-*)
        &lt;/Components&gt;
        &lt;FPanel /&gt; (optional description of panel life cycle callbacks)
        &lt;Move  /&gt; (optional description moves of panel because of events)
        &lt;FAction /&gt; (optional description of callback of events capture by application)
    &lt;/Panel&gt;
&lt;/Panels&gt;
</code></pre>
<h2 id="panel-components-section">Panel Components Section</h2>
<p>The components of a panel will be included in the panel’s components section.</p>
<h3 id="label-1">Label:</h3>
<pre><code>xml
&lt;Component Id="id. of component" Name="name of component" Type="label" display="normal|hidden|nSelect" (optional &gt;(0-*)
    &lt;Color&gt;color component&lt;/Color&gt; (optional)
    &lt;Dimension border="0|1" x="2" y="4" high="1" width="20"/&gt;
    &lt;Text&gt;Texto de la etiqueta&lt;/Text&gt; (0-*)
    &lt;Keymap&gt;own keymap&lt;/Keymap&gt; (optional)
    &lt;Move /&gt;(optional description moves of panel because of events)
    &lt;FAction /&gt; (optional description of callback of events capture by application)
    &lt;FComponent / (optional description of component life cycle callbacks)
&lt;/Component&gt;
</code></pre>
<h3 id="button-1">Button:</h3>
<pre><code>xml
&lt;Component Id="id. of component" Name="name of component" Type="button" display="normal|hidden|nSelect" (optional)&gt; (0-*)
    &lt;Color&gt;color component&lt;/Color&gt; (optional)
    &lt;Dimension border="0|1" x="2" y="4" high="1" width="20"/&gt;
    &lt;Text&gt;Texto del botón&lt;/Text&gt; (0-*)
    &lt;Keymap&gt;own keymap&lt;/Keymap&gt; (optional)
    &lt;Move /&gt;(optional description moves of panel because of events)
    &lt;FAction /&gt; (optional description of callback of events capture by application)
    &lt;FComponent / (optional description of component life cycle callbacks)
&lt;/Component&gt;
</code></pre>
<h3 id="check-button-2">Check Button:</h3>
<pre><code>xml
&lt;Component Id="Id. of component" Name="name of component" Type="ckbutton" Check="y|n"(optional) chIsCheck="character|number" (optional) chNoCheck="character|number" (optional) display="normal|hidden|nSelect" (optional) &gt;(0-*)
    &lt;Color&gt;noColor&lt;/Color&gt; (optional)
    &lt;Dimension border="0|1" x="2" y="3" high="1" width="40"/&gt;
    &lt;Text&gt;Text of de Check&lt;/Text&gt; (0-*)
    &lt;Keymap&gt;own keymap&lt;/Keymap&gt; (optional)
    &lt;Move /&gt; (optional description moves of panel because of events)
    &lt;FAction /&gt; (optional description of callback of events capture by application)
    &lt;FComponent /&gt; (optional description of component life cycle callbacks)
&lt;/Component&gt;
</code></pre>
<h3 id="list-button-1">List Button:</h3>
<pre><code>xml
&lt;Component Id="id. of component" Name="name of component" Type="lsbutton" display="normal|hidden|nSelect|open" (optional) &gt;(0-*)
    &lt;Color&gt;color component&lt;/Color&gt; (optional)
    &lt;Dimension border="0|1" x="2" y="4" high="1" width="20"/&gt;
    &lt;Text&gt;Texto del botón&lt;/Text&gt; (0-*)
    &lt;Keymap&gt;own keymap&lt;/Keymap&gt; (optional)
    &lt;Move /&gt;(optional description moves of panel because of events)
    &lt;FAction /&gt; (optional description of callback of events capture by application)
    &lt;FComponent / (optional description of component life cycle callbacks)
&lt;/Component&gt;
</code></pre>
<h3 id="field-1">Field</h3>
<pre><code>xml
&lt;Component Id="id. of component" Name="name of component" Type="field" display="normal|hidden|nSelect" (optional)&gt; (0-*)
    &lt;Color&gt;color component&lt;/Color&gt; (optional)
    &lt;Dimension border="0|1" x="2" y="4" high="1" width="20"/&gt;
    &lt;Edit chToEDIT="." (optional) editType="validate callback" (optional) auto="y|n" (optional) secret="y|n" (optional)/&gt; (optional)
    &lt;Text&gt;Texto inicial field&lt;/Text&gt; (0-*)
    &lt;Keymap&gt;own keymap&lt;/Keymap&gt; (optional)
    &lt;Move /&gt;(optional description moves of panel because of events)
    &lt;FAction /&gt; (optional description of callback of events capture by application)
    &lt;FComponent / (optional description of component life cycle callbacks)
&lt;/Component&gt;
</code></pre>
<h2 id="tables-section">Tables Section</h2>
<p>If the application uses tables, they will be defined in the Tables section.</p>
<pre><code>xml
&lt;Tables&gt; (optional)
    &lt;Table Id="Id. of the table" Name="name of the table" opToMade="none|hide|destroy" Level="level of the table"&gt; (0-*)
        &lt;Title&gt;View title&lt;/Title&gt; (optional)
        &lt;Dimension border="0|1" x="1" y="4" high="18" width="18"/&gt;
        &lt;Style head="0|1" vLine="0|1" (optional) hLine="0|1" (optional) colorHead="color cabecera"(optional) colorData="color data"(optional) /&gt;
        &lt;Elements&gt; (1-*)
            &lt;Element size="size"&gt;Title Field&lt;/Element&gt;
        &lt;/Elements&gt;
        &lt;Keymap&gt;own keymap&lt;/Keymap&gt; (optional)
        &lt;FTable /&gt; (optional description of table life cycle callbacks)
        &lt;Move /&gt; (optional description moves of panel because of events)
        &lt;FAction /&gt; (optional description of callback of events capture by application)
    &lt;/Table&gt;
&lt;/Tables&gt;
</code></pre>
<h2 id="edit-section">Edit Section</h2>
<p>If the application makes use of edit-type Views, the Edits section will be included.</p>
<pre><code>xml
&lt;Edits&gt; (optional)
    &lt;Edit Id="Id. of view" Name="name of View" opToMade="none|hide|destroy" Level="level of the View" ReadOnly="y" (optional)&gt; (0-*)
        &lt;Title&gt;View title&lt;/Title&gt; (optional)
        &lt;Dimension border="0|1" x="3" y="3" high="20" width="75"/&gt;
        &lt;Color&gt;view color&lt;/Color&gt; (optional)
        &lt;File&gt;file to load&lt;/File&gt; (optional)
        &lt;Keymap&gt;own keymap&lt;/Keymap&gt; (optional)
        &lt;Move /&gt; (optional description moves of panel because of events)
        &lt;FAction /&gt; (optional description of callback of events capture by application)
        &lt;FEdit /&gt; (optional description of edit life cycle callbacks)
    &lt;/Edit&gt;
&lt;/Edits&gt;
</code></pre>
<h2 id="move-section">Move Section</h2>
<p>If we use the move section.</p>
<pre><code>xml
&lt;Move enter="v:[c]" (optional)
out="v:[c]" (optional)
next="v:[c]" (optional)
previous="v:[c]" (optional)
up="v:[c]" (optional)
down="v:[c]" (optional)
left="v:[c]" (optional)
rigth="v:[c]" (optional)
F[0-11]="v:[c]" (optional) /&gt;
</code></pre>
<h2 id="faction-section">FAction Section</h2>
<p>In the capture of events by the application.</p>
<pre><code>xml
&lt;FAction enter="callback" (optional)
out="callback" (optional)
next="callback" (optional)
previous="callback" (optional)
up="callback" (optional)
down="callback" (optional)
left="callback" (optional)
rigth="callback" (optional)
Fn="callback" (optional) /&gt;
</code></pre>
<h2 id="fpanel-fcomponent-ftable-fedit-section">FPanel, FComponent, FTable, FEdit Section</h2>
<p>In the life cycle callbacks, the syntax would be similar in all cases:</p>
<pre><code>xml
&lt;FPanel| preCreate="callback" (optional)
preShow="callback" (optional)
preActivate="callback" (optional)
preDeactivate="callback" (optional)
preHide="callback" (optional)
preDestroy="callback" (optional)
postCreate="callback" (optional)
postShow="callback" (optional)
postActivate="callback" (optional)
postDeactivate="callback" (optional)
postHide="callback" (optional)
postDestroy="callback" (optional)
/&gt;
</code></pre>
<h1 id="api-programming">API Programming</h1>
<h2 id="structures">Structures</h2>
<p>The basic structures are included in tBasic.h and describe the types that support it.<br>
They can be directly manipulated by the user in the callbacks, but it is not advisable.<br>
In any case, let’s show the most important ones.</p>
<h3 id="ttext">tTEXT</h3>
<p>It is the basic structure that supports the information associated with each element.<br>
It consists of a pointer to a three-dimensional matrix of lines and fields (text) with its size, occupation, position, and some other characteristic.</p>
<pre><code>c
typedef struct {
  char *** text;   /* (information) */
  enum TMode mode; /* (is fixed or dynamic) */
  FILE * fd;       /* (file origin of information). */
  unsigned short delete; /* (delete or not with OP_DESTROY) */
  unsigned short resize; /* (reserve more space as needed) */
  unsigned short maxColumns; /* (maximum sizes reserved) */
  unsigned short maxLines;
  unsigned short maxFields;
  unsigned short nroColumns; /* (occupied sizes) */
  unsigned short nroLines;
  unsigned short nroFields;
  unsigned short actColumn; /* (current displayed position) */
  unsigned short actLine;
  unsigned short actField;
  unsigned short check;     /* (check by default). */
}tText,*tTextPtr;
</code></pre>
<h3 id="tdim">tDim</h3>
<p>Definition of the frame.</p>
<pre><code>c
typedef struct {
   unsigned short border;
   unsigned short x;
   unsigned short y;
   unsigned short alto;   /* height */
   unsigned short ancho;  /* width */
} tDim,*tDimPtr;
</code></pre>
<h3 id="tcursor">tCursor</h3>
<p>Cursor position.</p>
<pre><code>c
typedef struct {
   unsigned short x;
   unsigned short y;
} tCursor,*tCursorPtr;
</code></pre>
<h3 id="tchattr">tChAttr</h3>
<p>Supports the application’s colors.</p>
<pre><code>c
typedef struct {
   int colorpair; /* color pair background/foreground */
   int   attr;   /* set of WA* attributes */
}tChAttr,*tChAttrPtr;
</code></pre>
<h3 id="tstatus">tStatus</h3>
<p>Used within the application logic to manage the state of elements.</p>
<pre><code>c
typedef struct {
   enum EAlign align;    /* left|right */
   enum EDisplay visible; /* visible, hidden, open, not Selected */
   unsigned short ckCheck; /* check definition */
   unsigned short ckIsCheck;
   unsigned short ckNoCheck;
   unsigned short defCheck;
   unsigned short activa;  /* active or not */
   enum EInsert   insert;  /* Insert or replace */
   unsigned short multiLine; /* more than 1 line */
   unsigned short actField; /* current visible element */
   unsigned short actLine;
   unsigned short actColumn;
   unsigned short nactFields; /* number of visible elements */
   unsigned short nactLines;
   unsigned short nactColumns;
} tStatus,*tStatusPtr;
</code></pre>
<h3 id="feditcheck">feditCheck</h3>
<p>Describes the validation functions for the fields.</p>
<pre><code>c
typedef struct feditCheck{
  enum EditType tipo; /* predefined or user */
  enum EAlign  align;
  enum EInsert insert;
  int (*checkEdit)(int * caracter); /* user function */
  struct feditCheck * siguiente;    /* next */
} tfeditCheck, * tfeditCheckPtr;
</code></pre>
<h3 id="tedit">tEDIT</h3>
<p>Contains the specific information for field components.</p>
<pre><code>c
typedef struct {
   unsigned short secret; /* show with * */
   int chToEDIT;  /* display character */
   int editType; /* validation */
   unsigned short autoComplet;
} tEDIT, * tEDITPtr;
</code></pre>
<h3 id="tvisual">tVisual</h3>
<p>Master visualization structure with everything needed.</p>
<pre><code>c
typedef struct {
   WINDOW * win; /* ncurses window */
   WINDOW * wBack; /* ncurses window to restore */
   unsigned short scroll; /* has scroll */
   tChAttr color;  /* color */
   tDim dimension; /* dimension */
   tCursor cursor; /* cursor */
   tStatus status; /* status */
} tVisual,*tVisualPtr;
</code></pre>
<h3 id="tcomponent">tComponent</h3>
<p>Structure that defines the component.</p>
<pre><code>c
typedef struct miComponente{
   int id;
   char name[MAX_COMPONENT_NAME];
   enum CComponents type;
   void * parent;   /* panel it hangs from */
   tVisual * visual; /* visualization information */
   tText * text;     /* information to represent */
   tEDIT * editMode;  /* only for field types */
   tmapKeys * mapkey; /* key map */
   tMove * move;    /* movements */
   tFActionPanel * personalAction; /* user actions */
   tFComponent * personalFComponent; /* life cycle captures */
} tComponent, * tComponentPtr;
</code></pre>
<h3 id="tpanel">tPanel</h3>
<p>Structure that supports the panel.</p>
<pre><code>c
typedef struct {
   int id;
   char name[MAX_NAME_VIEW];
   unsigned short opToMade; /* when deleting */
   char title[MAX_VIEW_TITLE]; /* title */
   tVisual * visual;  /* visualization information */
   tFPanel * personalFPanel;
   tMove * move;
   tFActionPanel * personalAction;
   tlComponent * elements; /* list of components */
   tComponent * activeElement; /* active component */
} tPanel, * tPanelPtr;
</code></pre>
<h3 id="ttable">tTable</h3>
<p>Structure that supports tables.</p>
<pre><code>c
typedef struct {
   int id;
   char name[MAX_NAME_VIEW];
   unsigned short opToMade; /* when deleting */
   char title[MAX_VIEW_TITLE];
   tVisualPtr vTable;  /* Visual of the set head + data */
   tVisualPtr vHead; /* Visual of the header */
   tVisualPtr vData; /* Visual of the data */
   unsigned short vline; /* vertical line */
   unsigned short hline; /* horizontal line */
   unsigned short nColumns; /* number of visible columns */
   unsigned short nLines;  /* number of visible columns */
   tText * text;        /* data. */
   tmapKeys * mapkey;   /* keyboard map */
   tMove * move;
   tFActionTable * personalAction;
   tFTable * personalFTable;
   tTableColumnPtr columns; /* columns */
} tTable, * tTablePtr;

typedef struct tableColumn{
   char * title;            /* Column title */
   unsigned short len;      /* Size */
   struct tableColumn * next;
} tTableColumn, * tTableColumnPtr;
</code></pre>
<h3 id="tedit-1">tEdit</h3>
<p>Structure of the Edit view.</p>
<pre><code>c
typedef struct {
   int id;
   char name[MAX_NAME_VIEW];
   char file[MAX_NAME_FILE];
   unsigned short opToMade; /* when deleting */
   char title[MAX_VIEW_TITLE];
   tVisualPtr vHead; /* visual of the header */
   tVisualPtr vData; /* visual of the data. */
   tText * text;     /* current information */
   tmapKeys * mapkey; /* keyboard map */
   enum EMode mode;   /* ROnly or RW */
   tMove * move;
   tFActionEdit * personalAction;
   tFEdit * personalFEdit;
} tEdit, * tEditPtr;
</code></pre>
<h3 id="tview">tView</h3>
<p>The set of Views is supported by the tView structure.</p>
<pre><code>c
typedef struct {
 enum CViews type; /* panel/table/edit */
 unsigned short level; /* level */
 WINDOW * wBack;  /* window to show when hiding */
 tCaller caller;  /* who has called us. */
 union {
    tPanel * panel;
    tTable * table;
    tEdit * edit;
    } view;
}tView,*tViewPtr;
</code></pre>
<p>We skip the description of the structures tmapKeys, tMove, tFactionPanel and tFComponent as they are trivial.</p>
<h2 id="api">API</h2>
<h3 id="errors-1">Errors</h3>
<p>The API for error handling is included in the file error.h.</p>
<pre><code>c
/*
 * Initialization, refer if must print the errors and the file to do.
 * by default no print
 */
void ERR_printError(int print,char * file);

/* Declare a fatal error, print the message and exit */
void ERR_fatalError(int error, char* format,...);

/* Declare a regular error. */
void ERR_Error(int error, char * format,... );

/* Indicate if error */
int ERR_isError();

/* Return the last error if any and restore a no error. */
int ERR_lastError();
</code></pre>
<h3 id="colors-1">Colors</h3>
<p>Colors are managed with the API included in the header color.h.</p>
<pre><code>c
/* Initialize the colors, Mandatory */
int COLOR_inicializar(unsigned short useColor);
/* Get the pair color for a bg, fg color */
int COLOR_get(unsigned short bg, unsigned short fg);
/* Get the bg of a colorpair */
int COLOR_getBackground(int colorpair );
/* Get the fg of a colorpair */
int COLOR_getForeground(int colorpair );
/* Add the WA font to color struct */
int COLOR_Attrb(tChAttr * color,int attributo);
</code></pre>
<h3 id="msgs-1">Msgs</h3>
<p>The API for handling warning Views is declared in the header msg.h.</p>
<pre><code>c
/* MSG initialize, mandatory */
void MSG_Init();
/* Open a msg View */
int MSG_create(enum CMsg type, unsigned int center, char * formato,...);
/* change msg View color */
void MSG_borderColor(enum CMsg type, unsigned short border,tChAttr * color);
/* change msg View */
void MSG_txtButton(enum CMsg type,
                   char * title,
                   unsigned short nButtons,
                   char * text1, char * text2);

/* Set close timeout msg View with 0 buttons */
void MSG_setSegInfo(unsigned int nseg);
</code></pre>
<h3 id="keymap-1">KeyMap</h3>
<p>Keymap management is performed by the keys class; the API can be found in keys.h.</p>
<pre><code>c
/* initialize, Mandatory */
int KEYS_iniatilize();

/* define a new mapKey */
int KEYS_newMapKey(char * nomMapKeys, tmapKeys * mapKey);
tmapKeys * KEYS_getMapKey(char * nomMapKeys);
/* declare use mouse */
void KEYS_setMouse(int mouse);
/* get if use mouse */
int KEYS_getMouse();
</code></pre>
<h3 id="check-field-functions">Check field functions</h3>
<p>In the header fedit.h is the definition of the prototype to include a new check function for field components.</p>
<pre><code>c
/* Add a Function Check for a Field component */
int FEDIT_addCheck(unsigned short tipo, unsigned short align,
                  unsigned short insert,
                  int (*checkEdit)(int * caracter));
</code></pre>
<h3 id="data-passing">Data Passing</h3>
<p>Sometimes it may be necessary to pass data between Views, or more clearly, between user callbacks.<br>
For this, a FILO stack (First Input Last Output) is provided, in which texts can be deposited for later retrieval.<br>
The interface is part of the text class included in text.h and has two functions:</p>
<pre><code>c
/* Insert in a FILO pile data, optional init FILO */
int TEXT_send(char * texto,int init);
/* Extract from the FILO pile */
char * TEXT_recv();
</code></pre>
<p><strong>No Memory Reservation</strong>: The <code>TEXT_send</code> function <strong>does NOT copy or reserve memory</strong> for the text. It simply stores the <strong>pointer</strong> (<code>char*</code>) passed to it.</p>
<pre><code>c
#define MAX_PILE      40
typedef struct{
    char * text[MAX_PILE];
    unsigned short rbuffer;
}tBufferSnd;
</code></pre>
<h3 id="text">Text</h3>
<p>Low-level data manipulation is performed via the Text class, whose interface is included in text.h.<br>
The interface is complex and should be avoided unless necessary.</p>
<h4 id="initial-creation-of-the-structure">Initial creation of the structure:</h4>
<pre><code>c
/* Create a new struct for the text, reserve the memory. */
tText * TEXT_new(int resize, unsigned short delete,int maxData, int nroLines,int nroFields);
/* Create a new struct for the text of a tEdit View, don't reserve the memory. */
tText * TEXT_newEdit(int maxData, int nroLines,unsigned short mustDelete);
</code></pre>
<h4 id="manipulation">Manipulation:</h4>
<pre><code>c
/* add a simple Text must contain (\n) */
tText * TEXT_newSimpleText(tDim * dim, char * newText,unsigned short delete);
/* add a multiple Text to a component, in field 0 */
tText * TEXT_newSimpleLineText(tDim * dim, char ** newText,unsigned short delete);
/* add a Text must contain (\n) int field 0 */
int TEXT_addSimpleLine(tText * miText, char * newText);
/* delete Text contain text */
int TEXT_delSimpleData(tText * miText, char * text);
/* replace the Text in a line, field */
int TEXT_replaceLine(tText * miText,int line,int field,char * text);
/* delete all fields from a line */
int TEXT_delLine(tText * miText,unsigned short  line);
/* delete the line contain text */
int TEXT_delLineText(tText * miText,char * text);
Multiple field manipulation:
</code></pre>
<h4 id="specific-case-of-tables">Specific case of tables:</h4>
<pre><code>c
/* Add data in line+field active */
int TEXT_addData(tText * miText, char * data);
/* Del data contain data */
int TEXT_delData(tText * miText, char * data,int global);
/* Del multiple fields data */
int TEXT_addLine(tText * miText, int columns, char * data[]);
/* Del line contain data */
int TEXT_delDataLine(tText * miText, char * data[],int global);
</code></pre>
<h4 id="file-based-manipulation">File-based manipulation:</h4>
<pre><code>c
/* load the file into the text */
int TEXT_loadFile(tText * miText, char  * fileName);
/* load the file into a table */
int TEXT_loadTableFile(tText * miText,char  * fileName,char separator);
/* save the text to a file */
int TEXT_saveFile(tText * miText, char  * fileName);
/* save the text to a file with separators */
int TEXT_saveTabFile(tText * miText, char  * fileName, char separator);
</code></pre>
<h4 id="retrieval">Retrieval:</h4>
<p>Obtain the information:</p>
<pre><code>c
/* Get char at line,field, column */
char TEXT_getChar(tText * miText,int line,int field,int column);
/* Get data at line,field */
char * TEXT_getData(tText * miText, int line,int field);
/* Get data line at line */
char ** TEXT_getLine(tText * miText, unsigned short line);
/* Get all data at field */
char ** TEXT_getField(tText * miText, unsigned short field);
/* Iterate getData */
char * TEXT_nextData(tText * miText, int field);
</code></pre>
<h3 id="component">Component</h3>
<p>For interaction with components, in the header component.h we find the following functions:</p>
<h4 id="creation">Creation</h4>
<pre><code>c
/*
 * Create a component */
tComponent * COMPONENT_create(tPanel * panel,
                        int id,
                        char * name,
                        enum CComponents type,
                        tDim * dimension,
                        tChAttr * color,
                        tmapKeys * mapkey,
                        tMove * move,
                        _tFActionPanel * personalAction,
                        _tFComponent * personalFComponent);
/*
 * Add the editMode to a field component */
void COMPONENT_createEdit(tComponent * component, tEDIT * editMode);
</code></pre>
<h4 id="manipulation-1">Manipulation</h4>
<pre><code>c
/*
 * Change component display */
void COMPONENT_display(tComponent * component, enum EDisplay display);
/*
 * Change the edit Mode */
int COMPONENT_editMode(tComponent * component, enum EInsert mode);
/* Change color */
int COMPONENT_changeColor(tComponent * component, tChAttr * color);

/* Set the text component */
int COMPONENT_simpleText(tComponent * component, char * text,
                        unsigned short delete);

/* Initialize the component text */
int COMPONENT_clean(tComponent * component);
/* Add a text to the component */
int COMPONENT_addText(tComponent * component,char * texto);

/* Delete a text from the component */
int COMPONENT_delText(tComponent * component,char * texto);

/* Change the component text */
int COMPONENT_setText(tComponent * component,char * text);

/* Replace the Text and rewrite */
int COMPONENT_changeText(tComponent * component ,char * text);

/* Rewrite the component */
int COMPONENT_refresh(tComponent * component);
</code></pre>
<h4 id="set--get">Set &amp; Get</h4>
<pre><code>c
/* Get the Text */
char * COMPONENT_getText(tComponent * component);
/* Get the Value */
char * COMPONENT_getValue(tComponent * component);
/* Get the select value and line */
char * COMPONENT_getSelectValue(tComponent * component,int * line);

/* Set the Value */
int COMPONENT_setValue(tComponent * component,char * texto);
/* Set select value by line or by text */
int COMPONENT_setSelectValue(tComponent * component,int line,char * texto);
/* Is the text value select */
int COMPONENT_isValue(tComponent * component,char * text);
</code></pre>
<h3 id="panel-2">Panel</h3>
<p>In the header panel.h we find the following functions:</p>
<h4 id="creation-1">Creation</h4>
<pre><code>c
/*
 * create Panel */
tView * PANEL_create(int id,
                      char * name,
                      unsigned short level,
                      char * title,
                      tDim * dimension,
                      tChAttr * color,
                      unsigned short opToMade,
                      tMove * move,
                      _tFActionPanel * personalAction,
                      _tFPanel * personalFPanel);

/*
 * Add a component to the panel. */
int PANEL_addComponent(tPanel * panel,
                       tComponent * componente);
/*
 * Del a component from the panel */
int PANEL_delComponent(tPanel * panel,
                       short id,  char * name);
</code></pre>
<h4 id="search">Search</h4>
<pre><code>c
/* get the active panel */
tPanel * PANEL_getActivePanel();
/*
 * Search component */
tComponent * PANEL_searchComponent(tPanel * panel,
                       char * name);
/*
 * search the component at X,Y if any */
char * PANEL_searchXYComponent(tPanelPtr panel,int x,int y);
</code></pre>
<h4 id="manipulation-2">Manipulation</h4>
<pre><code>c
/* Change panel dimension */
int  PANEL_changeDim(tPanel * panel,
                  tDim * dimension);

/* Change panel color */
int  PANEL_changeColor(tPanel * panel,
                  tChAttr * color);

/* Rewrite the panel */
int PANEL_refresh(tPanel * panel);
</code></pre>
<h3 id="tables-1">Tables</h3>
<p>From table.h:</p>
<h4 id="create">Create</h4>
<pre><code>c
/*
 * Create the table. */
tView * TABLE_create(int id,
                      char * name,
                      unsigned short level,
                      char * title,
                      tDim * dimension,
                      tChAttr * colorHead,
                      tChAttr * colorData,
                      unsigned short opToMade,
                      unsigned short head,
                      unsigned short vline,
                      unsigned short hline,
                      tmapKeys * mapkey,
                      tMove * move,
                      _tFActionTable * personalAction,
                      _tFTable * personalFTable);

/* Set the table text. */
void TABLE_text(tTable * table, tText * text);

/* Add a table column. */
int TABLE_addColumn(tTable * table,
                    char * title, unsigned int len);

/*
 * Set column head . */
int TABLE_setColumnHead(tTable * table, int column,char * data);
</code></pre>
<h4 id="get--set">Get &amp; Set</h4>
<pre><code>c
/*
 * Get Value select */
char ** TABLE_getValue(tTable * table);
char * TABLE_getColumnValue(tTable * table,int column);

/*
 * Get Table text */
char ** TABLE_getText(tTable * table);
char * TABLE_getTextValue(tTable * table,int column);
</code></pre>
<h4 id="manipulation-3">Manipulation</h4>
<pre><code>c
/* Change table colors */
int  TABLE_changeColor(tTable * table,
                  tChAttr * colorHead,
                  tChAttr * colorData);
/* Rewrite the table*/
int TABLE_refresh(tTable * table);
</code></pre>
<h3 id="edit-2">Edit</h3>
<p>The edit View API is located in edit.h.</p>
<h4 id="creation-2">Creation</h4>
<pre><code>c
/*
 * Create the View. */
tView * EDIT_create(int id,
                      char * name,
                      unsigned short level,
                      char * title,
                      tDim * dimension,
                      tChAttr * color,
                      unsigned short opToMade,
                      enum EMode mode,
                      tmapKeys * mapkey,
                      tMove * move,
                      _tFActionEdit * personalAction,
                      _tFEdit * personalFEdit);

/*
 * Set the edit text */
void EDIT_Text(tEdit * edit,tText * text);
</code></pre>
<h4 id="manipulation-4">Manipulation</h4>
<pre><code>c
 /* Change color the View. */
int  EDIT_changeColor(tEdit * edit, tChAttr * color);
 /* Rewrite edit . */
int EDIT_refresh(tEdit * edit);
Get &amp; set
c
/* load a File */
int EDIT_loadFile(tEdit * edit,char * fileName,int maxData, int iniLines);
/* save to a File */
int EDIT_saveFile(tEdit * edit);
</code></pre>
<h3 id="views">Views</h3>
<p>From view.h and lview.h.</p>
<h4 id="locate-component">Locate component</h4>
<pre><code>c
/*
 * Get Active View. */
tViewPtr VIEW_getActive();
/*
 * Get the View or component. */
void * LVIEW_getElement(char * nView, char * nComponent);
/*
 * locate a View */
tView * LVIEW_searchView(char * name);
</code></pre>
<h4 id="process">Process</h4>
<pre><code>c
/*
 * Process the View. */
void VIEW_Loop(tView * view, char * element);
</code></pre>
<h3 id="tui">TUI</h3>
<p>Initialization of the library is performed by calling:</p>
<pre><code>c
/* Init the TUI library */
SCREEN * TUI_init (unsigned int useMouse, unsigned int useColor);
/* End TUI */
void TUI_end();
</code></pre>
<p>which is located in tui.h and initializes the mandatory modules, returning the pointer to the ncurses SCREEN.</p>
<h1 id="direct-use">Direct Use</h1>
<p>As we have already indicated, it is possible to obviate the use of generation from XML and the graphical tool tUI and program the interface directly using only the TUI library.<br>
The API has already been described, so we will simply create a simple example to show this.<br>
In the following example, the menu1 we have been seeing is manually created.</p>
<pre><code>c
#include &lt;string.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;ncurses.h&gt;
#include &lt;tui.h&gt;

SCREEN * scrSTD;

tChAttr noColor;
tChAttr colorMenu;

/*
 * Create the first button
 */
static tComponentPtr _Cmenu_boton1(tPanelPtr panel) {
tChAttrPtr pColor=&amp;colorMenu;
tDim pDim ={1,0,0,3,10}; /* Border, X, Y ,High,Width */
tComponentPtr elemento;
tMove move = {
   "", "",
   ":boton2", ":boton2", "", "",
   ":boton2", ":boton2", {"","","","","","","","","","","",""}, ""
   };

  _tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
  memset(auxFC,0,sizeof(_tFComponent)); /* Not user Functions */
  _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
  memset(auxFA,0,sizeof(_tFActionPanel)); /* Not action user Functions */
  elemento=COMPONENT_create(panel,0,"boton1",1,&amp;pDim,pColor,
                         NULL /* Default keymap */,&amp;move,auxFA,auxFC);
  COMPONENT_simpleText(elemento,"OPCION A",0);
 return elemento;
}

/*
 * Create button2
 */
static tComponentPtr _Cmenu_boton2(tPanelPtr panel) {
tChAttrPtr pColor=&amp;colorMenu;
tDim pDim ={1,12,0,3,10}; /* Border, X, Y ,High,Width */
tComponentPtr elemento;
tMove move = {
   "", "", ":boton1", ":boton1", "", "",
   ":boton1", ":boton1", {"","","","","","","","","","","",""}, ""
   };
 _tFComponent * auxFC=(_tFComponent *)malloc(sizeof(_tFComponent));
  memset(auxFC,0,sizeof(_tFComponent)); /* Not user Functions */
  _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
  memset(auxFA,0,sizeof(_tFActionPanel)); /* Not action user Functions */
  elemento=COMPONENT_create(panel,0,"boton2",1,&amp;pDim,pColor,
  NULL /* Default Keymap */,&amp;move,auxFA,auxFC);
  COMPONENT_simpleText(elemento,"OPCION B",0);
 return elemento;
}

/*
 * Create the menu
 */
static tViewPtr _Pmenu1() {
tChAttrPtr pColor=&amp;colorMenu;
tDim pDim ={0,0,0,3,40}; /* No border, X-Y,High,Width */
tComponentPtr componente;
tViewPtr view;

  _tFPanel * auxFP=(_tFPanel *)malloc(sizeof(_tFPanel));
  memset(auxFP,0,sizeof(_tFPanel)); /* Not user Functions */
  _tFActionPanel * auxFA=(_tFActionPanel *)malloc(sizeof(_tFActionPanel));
  memset(auxFA,0,sizeof(_tFActionPanel)); /* Not action user Function */
  tMove move = {
   "", "exit:", "", "", "", "", "", "",
   {"","","","","","","","","","","",""}, ""
   };

  view=PANEL_create(0,"menu1",1,"",&amp;pDim,pColor,0,&amp;move,auxFA,auxFP);
  componente = _Cmenu_boton1(view-&gt;view.panel);
  PANEL_addComponent(view-&gt;view.panel, componente); /* Add component to Panel */
  componente = _Cmenu_boton2(view-&gt;view.panel);
  PANEL_addComponent(view-&gt;view.panel, componente); /* Add component to Panel */
 return view;
}

int main(int argc, char * argv[])
{
  tViewPtr view;

   scrSTD=TUI_init(1,1);  /* init with color and mouse */

   /* Create Colors */
   noColor.colorpair=COLOR_get(0,7);
   noColor.attr=0;
   colorMenu.colorpair=COLOR_get(2,0);
   colorMenu.attr=0;

   ERR_printError(1,"errors.err"); /* Print errors in error.err */
   view = _Pmenu1(); /* create the panel */

   VIEW_Loop(view,"boton1"); /* Control to boton1 of menu */

   TUI_end();

  return 0;
}
</code></pre>
<p>In the example we observe:</p>
<ul>
<li>We initialize the library and create a couple of colors.<br>
Additionally, we indicate that we want error printing and the file<br>
where we want them.</li>
<li>Next, we create the menu1 panel according to the dimensions, color,<br>
etc.</li>
<li>Within the panel creation, we also create the button components<br>
according to the dimension,… and associate them with the panel.</li>
<li>We only need to give control to menu1 and component1.</li>
<li>Finally, and so as not to end with a messed-up terminal, we call the<br>
library termination.</li>
</ul>
<p>If we had other panels or Views, we would act similarly: we would create them with the appropriate parameters and finally give control to the starting point of the application.</p>
<blockquote>
<p>The code generated by the XML generator follows this same mechanism, generating the code in <code>project_name.c</code> and can serve as a guide if you have any doubt.</p>
</blockquote>

