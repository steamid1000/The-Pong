### Button Auto-Size
    If the text size is given but also the button size is set then the text-size will be changed to auto fit
    the given button size.
    So if you want your button size to frow according to the text you enter then just dont call the 'SetSize'
    function on the object and it will work.
    ##### You can and should call the 'SetPosition' function to set the buttons position to the desired position.
    ##### The text position inside the buttons does not require any changing on the coders part, just change the button position and it will automatically center itself in the button.


### Font
    The font is required only once in the scene, the other objects use the same provided font file.
    ####Note: Please call the 'SetFont' function before creating any other objects like lables and buttons.