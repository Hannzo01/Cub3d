
Parsing rules:
- Map must always be the last element (no params after it).
- Map cannot contain empty lines (invalid).
- Parameters (NO, SO, WE, EA, F, C) can appear in any order.
- Parameters can be separated by one or more empty lines.
	(ex : NO ./north.xpm

		SO ./south.xpm



		WE ./west.xpm
		EA ./east.xpm )
- Parameters can have multiple spaces between type and value. (ex : NO   	     ./north.xpm,F  	  220,100,0)


NO kenza ./path_to_the_north_texture  ---> is invalid 
THE RULE : <ELEMENT_TYPE> [spaces] <VALUE>



C # F:

• Your program must be able to set the floor and ceiling colors to two different ones. 


	// khas ncheck wch mkynch empty string wst map
	// check if there are characters 0 1 N E W S ''

	// check boundaries if 1 or ' '
	// save personnage pos
	// ONLY One of NEWS
	// Flood fill on another copy
	// if invalid field of struct is 1 after flood fill invalid map
	// ready to render

	

	-----MLX_PART-----

	The memory is one long array of bytes representing all pixels row by row.


	~RENDERING~ draw everything on screen
	
	
Cell (1,1) in map → Pixels (64,64) to (127,127) on screen
├── pixel_x_start = 64, pixel_y_start = 64
├── pixel_x goes from 64 to 127
└── pixel_y goes from 64 to 127