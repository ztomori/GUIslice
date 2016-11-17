#ifndef _MICROSDL_H_
#define _MICROSDL_H_

// =======================================================================
// microSDL library
// - Calvin Hass
// - http://www.impulseadventure.com/elec/microsdl-sdl-gui.html
//
// - Version 0.5.1    (2016/11/16)
// =======================================================================

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
  
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>

  
// -----------------------------------------------------------------------
// Configuration
// -----------------------------------------------------------------------

#define MSDL_ELEM_STRLEN_MAX  120  // Max string length of text elements

// Enable for bitmap transparency and definition of color to use
#define MSDL_BMP_TRANS_EN     1               // 1 = enabled, 0 = disabled
#define MSDL_BMP_TRANS_RGB    0xFF,0x00,0xFF  // RGB color (default:pink)

// -----------------------------------------------------------------------
// Enumerations
// -----------------------------------------------------------------------

  /// Element ID enumerations
  /// - The Element ID is the primary means for user code to
  ///   reference a graphic element.
  /// - Application code can assign arbitrary Element ID values
  ///   in the range of 0...32767
  /// - Specifying MSDL_ID_AUTO to ElemCreate() requests that
  ///   microSDL auto-assign an ID value for the Element. These
  ///   auto-assigned values will begin at MSDL_ID_AUTO_BASE.
  /// - Negative Element ID values are reserved 
  typedef enum {
    // Public usage
    MSDL_ID_USER_BASE       = 0,      ///< Starting Element ID for user assignments
    MSDL_ID_NONE            = -1999,  ///< No Element ID has been assigned
    MSDL_ID_AUTO,                     ///< Auto-assigned Element ID requested
    MSDL_ID_TEMP,                     ///< ID for Temporary Element
    // Internal usage
    MSDL_ID_AUTO_BASE       = 32768,  ///< Starting Element ID to start auto-assignment
                                      ///< (when MSDL_ID_AUTO is specified)            
  } microSDL_teElemId;


  /// Page ID enumerations
  /// - The Page ID is the primary means for user code to
  ///   reference a specific page of elements.
  /// - Application code can assign arbitrary Page ID values
  ///   in the range of 0...32767
  /// - Negative Page ID values are reserved   
  typedef enum {
    // Public usage
    MSDL_PAGE_USER_BASE     = 0,      ///< Starting Page ID for user assignments
    // Internal usage
    MSDL_PAGE_NONE          = -2999,  ///< No Page ID has been assigned
  } microSDL_tePageId;

  /// View ID enumerations
  /// - The View ID is the primary means for user code to
  ///   reference a specific viewport.
  /// - Application code can assign arbitrary View ID values
  ///   in the range of 0...32767
  /// - Negative View ID values are reserved   
  typedef enum {
    // Public usage
    MSDL_VIEW_ID_USER_BASE  = 0,      ///< Starting Page ID for user assignments
    MSDL_VIEW_ID_SCREEN     = -3999,  ///< Default Viewport ID used for main screen
    // Internal usage
    MSDL_VIEW_ID_NONE,                ///< No Viewport ID has been assigned
  } microSDL_teViewId;

  /// Group ID enumerations
  typedef enum {
    // Public usage
    MSDL_GROUP_ID_USER_BASE = 0,      ///< Starting Group ID for user assignments
    // Internal usage
    MSDL_GROUP_ID_NONE      = -6999,  ///< No Group ID has been assigned
  } microSDL_teGroupId;
  
  /// Font ID enumerations
  /// - The Font ID is the primary means for user code to
  ///   reference a specific font.
  /// - Application code can assign arbitrary Font ID values
  ///   in the range of 0...32767
  /// - Negative Font ID values are reserved    
  typedef enum {
    // Public usage
    MSDL_FONT_USER_BASE     = 0,      ///< Starting Font ID for user assignments
    MSDL_FONT_NONE          = -4999,  ///< No Font ID has been assigned
  } microSDL_teFontId;
  

  /// View Index enumerations
  /// - The View Index is used for internal purposes as an offset
  //    into the GUI's array of views
  typedef enum {
    // Internal usage
    MSDL_VIEW_IND_NONE      = -5999,  ///< No Viewport Index is available
    MSDL_VIEW_IND_SCREEN,             ///< Default Viewport Index used for main screen
  } microSDL_teViewInd;
  
  /// Element Index enumerations
  /// - The Element Index is used for internal purposes as an offset
  //    into the GUI's array of elements
  typedef enum {
    // Internal usage
    MSDL_IND_NONE           = -9999,  ///< No Element Index is available
    MSDL_IND_FIRST          = 0,      ///< User elements start at index 0
  } microSDL_teElemInd;


/// Element type
typedef enum {
    // Core elements:
    MSDL_TYPE_NONE,         ///< No element type specified
    MSDL_TYPE_BKGND,        ///< Background element type
    MSDL_TYPE_BTN,          ///< Button element type
    MSDL_TYPE_TXT,          ///< Text label element type
    MSDL_TYPE_BOX,          ///< Box / frame element type
    MSDL_TYPE_LINE,         ///< Line element type
    // Extended elements:
    MSDL_TYPEX_GAUGE,       ///< Guage / progressbar extended element
    MSDL_TYPEX_CHECKBOX,    ///< Checkbox extended element
    MSDL_TYPEX_SLIDER,      ///< Slider extended element
    MSDL_TYPEX_SELNUM,      ///< SelNum extended element
} microSDL_teType;

// Element text alignment
#define MSDL_ALIGNV_TOP       0x10                                ///< Vertical align to top
#define MSDL_ALIGNV_MID       0x20                                ///< Vertical align to middle
#define MSDL_ALIGNV_BOT       0x40                                ///< Vertical align to bottom
#define MSDL_ALIGNH_LEFT      0x01                                ///< Horizontal align to left
#define MSDL_ALIGNH_MID       0x02                                ///< Horizontal align to middle
#define MSDL_ALIGNH_RIGHT     0x04                                ///< Horizontal align to right
#define MSDL_ALIGN_TOP_LEFT   MSDL_ALIGNH_LEFT  | MSDL_ALIGNV_TOP ///< Align to top-left
#define MSDL_ALIGN_TOP_MID    MSDL_ALIGNH_MID   | MSDL_ALIGNV_TOP ///< Align to middle of top
#define MSDL_ALIGN_TOP_RIGHT  MSDL_ALIGNH_RIGHT | MSDL_ALIGNV_TOP ///< Align to top-right
#define MSDL_ALIGN_MID_LEFT   MSDL_ALIGNH_LEFT  | MSDL_ALIGNV_MID ///< Align to middle of left side
#define MSDL_ALIGN_MID_MID    MSDL_ALIGNH_MID   | MSDL_ALIGNV_MID ///< Align to center
#define MSDL_ALIGN_MID_RIGHT  MSDL_ALIGNH_RIGHT | MSDL_ALIGNV_MID ///< Align to middle of right side
#define MSDL_ALIGN_BOT_LEFT   MSDL_ALIGNH_LEFT  | MSDL_ALIGNV_BOT ///< Align to bottom-left
#define MSDL_ALIGN_BOT_MID    MSDL_ALIGNH_MID   | MSDL_ALIGNV_BOT ///< Align to middle of bottom
#define MSDL_ALIGN_BOT_RIGHT  MSDL_ALIGNH_RIGHT | MSDL_ALIGNV_BOT ///< Align to bottom-right


// Basic color definition
#define MSDL_COL_BLUE_DK    (microSDL_Color) {0,0,255}       ///< Blue (dark)
#define MSDL_COL_BLUE_LT    (microSDL_Color) {128,128,255}   ///< Blue (light)
#define MSDL_COL_RED_DK     (microSDL_Color) {255,0,0}       ///< Red (dark)
#define MSDL_COL_RED_LT     (microSDL_Color) {255,128,128}   ///< Red (light)
#define MSDL_COL_GREEN_DK   (microSDL_Color) {0,255,0}       ///< Green (dark)
#define MSDL_COL_GREEN_LT   (microSDL_Color) {128,255,128}   ///< Green (light)
#define MSDL_COL_YELLOW     (microSDL_Color) {255,255,0}     ///< Yellow
#define MSDL_COL_YELLOW_DK  (microSDL_Color) {64,64,0}       ///< Yellow (dark)
#define MSDL_COL_BLACK      (microSDL_Color) {0,0,0}         ///< Black
#define MSDL_COL_GRAY_DK    (microSDL_Color) {64,64,64}      ///< Gray (dark)
#define MSDL_COL_GRAY       (microSDL_Color) {128,128,128}   ///< Gray
#define MSDL_COL_GRAY_LT    (microSDL_Color) {192,192,192}   ///< Gray (light)
#define MSDL_COL_WHITE      (microSDL_Color) {255,255,255}   ///< White
#define MSDL_COL_PURPLE     (microSDL_Color) {128,0,128}     ///< Purple
#define MSDL_COL_CYAN       (microSDL_Color) {0,255,255}     ///< Cyan
#define MSDL_COL_MAGENTA    (microSDL_Color) {255,0,255}     ///< Magenta
#define MSDL_COL_TEAL       (microSDL_Color) {0,128,128}     ///< Teal
#define MSDL_COL_ORANGE     (microSDL_Color) {255,165,0}     ///< Orange
#define MSDL_COL_BROWN      (microSDL_Color) {165,42,42}     ///< Brown

/// Touch event type for element touch tracking
typedef enum  {
    MSDL_TOUCH_DOWN_IN,    /// Touch event (down) inside element, start tracking
    MSDL_TOUCH_MOVE_IN,    /// Touch event (move/drag) inside tracked element
    MSDL_TOUCH_MOVE_OUT,   /// Touch event (move/drag) outside tracked element
    MSDL_TOUCH_UP_IN,      /// Touch event (up) inside tracked element
    MSDL_TOUCH_UP_OUT,     /// Touch event (up) outside tracked element
} microSDL_teTouch;


// -----------------------------------------------------------------------
// Types
// -----------------------------------------------------------------------

/// Callback function for element drawing
typedef bool (*MSDL_CB_DRAW)(void* pvGui,void* pvElem);

/// Callback function for element touch tracking
typedef bool (*MSDL_CB_TOUCH)(void* pvGui,void* pvElem,microSDL_teTouch eTouch,int nX,int nY);

/// Callback function for element tick
typedef bool (*MSDL_CB_TICK)(void* pvGui,void* pvElem);


// -----------------------------------------------------------------------
// Structures
// -----------------------------------------------------------------------


/// Rectangular region. Defines X,Y corner coordinates plus dimensions.
typedef struct microSDL_Rect {
  int16_t   x;    ///< X coordinate of cornder
  int16_t   y;    ///< Y coordinate of corner
  uint16_t  w;    ///< Width of region
  uint16_t  h;    ///< Height of region
} microSDL_Rect;

/// Color structure. Defines RGB triplet.
typedef struct microSDL_Color {
  uint8_t r;      ///< RGB red value
  uint8_t g;      ///< RGB green value
  uint8_t b;      ///< RGB blue value
  uint8_t unused; ///< Unused value to pad structure
} microSDL_Color;


// Forward declaration so we can have element reference in element
typedef struct microSDL_tsElem microSDL_tsElem;

///
/// Element Struct
/// - Represents a single graphic element in the microSDL environment
/// - A page is made up of a number of elements
/// - Each element is created with a user-specified ID for further
///   accesses (or MSDL_ID_AUTO for it to be auto-generated)
/// - Display order of elements in a page is based upon the creation order
/// - Extensions to the core element types is provided through the
///   pXData reference and pfuncX* callback functions.
///
typedef struct microSDL_tsElem {

  int                 nId;            ///< Element ID specified by user
  microSDL_teType     nType;          ///< Element type enumeration
  microSDL_Rect       rElem;          ///< Rect region containing element
  int                 nGroup;         ///< Group ID that the element belongs to  
  bool                bValid;         ///< Element was created properly
  
  bool                bGlowEn;        ///< Enable glowing visual state
  bool                bGlowing;       ///< Element is currently glowing
  
  void*               pvSurfNorm;     ///< Surface ptr to draw (normal)
  void*               pvSurfGlow;     ///< Surface ptr to draw (glowing)

  bool                bClickEn;       ///< Element accepts touch events
  bool                bFrameEn;       ///< Element is drawn with frame
  bool                bFillEn;        ///< Element is drawn with inner fill.
                                      ///< This is also used during redraw to determine
                                      ///< if elements underneath are visible and must
                                      ///< be redrawn as well.

  microSDL_Color      colElemFrame;   ///< Color for frame
  microSDL_Color      colElemFill;    ///< Color for background fill
  microSDL_Color      colElemGlow;    ///< Color to use when touch cause glowing

  bool                bNeedRedraw;    ///< Element needs to be redrawn

  /// Parent element reference. Used during redraw
  /// to notify parent elements that they require
  /// redraw as well. Primary usage is in compound
  /// elements.
  microSDL_tsElem*    pElemParent;  
  
  char                acStr[MSDL_ELEM_STRLEN_MAX];  ///< Text string to overlay
  microSDL_Color      colElemText;    ///< Color of overlay text
  unsigned            eTxtAlign;      ///< Alignment of overlay text
  unsigned            nTxtMargin;     ///< Margin of overlay text within rect region
  void*               pvTxtFont;      ///< Void ptr to Font for overlay text

  void*               pXData;         ///< Ptr to extended data structure
  
  MSDL_CB_DRAW        pfuncXDraw;     ///< Callback func ptr for drawing
  MSDL_CB_TOUCH       pfuncXTouch;    ///< Callback func ptr for touch
  MSDL_CB_TICK        pfuncXTick;     ///< Callback func ptr for timer/main loop tick
  
} microSDL_tsElem;


/// Element collection struct
/// - Collections are used to maintain a list of elements and any
///   touch tracking status.
/// - Pages and Compound Elements both instantiate a Collection
typedef struct {
  microSDL_tsElem*      pElemParent;      ///< Pointer to parent element (or NULL if none))

  microSDL_tsElem*      asElem;           ///< Array of elements
  unsigned              nElemMax;         ///< Maximum number of elements to allocate
  unsigned              nElemCnt;         ///< Number of elements allocated
  unsigned              nElemAutoIdNext;  ///< Next Element ID for auto-assignment
  
  microSDL_tsElem*      pElemTracked;     ///< Element currently being touch-tracked (NULL for none)
} microSDL_tsCollect;


/// Font reference structure
typedef struct {
  int     nId;      ///< Font ID specified by user
  void*   pvFont;   ///< Void ptr to the Font (type defined by driver)
} microSDL_tsFont;


/// Viewport structure
/// - Viewports allow drawing operations to be done within
///   a local coordinate system and clipped to a region.
typedef struct {
  int               nId;        ///< View ID specified by user
  microSDL_Rect     rView;      ///< Rect defining the viewport
  unsigned          nOriginX;   ///< Position within rView for local origin
  unsigned          nOriginY;   ///< Position within rView for local origin
} microSDL_tsView;


/// Page structure
/// - A page contains a collection of elements
/// - Many redraw functions operate at a page level
/// - Maintains state as to whether redraw or screen flip is required
typedef struct {

  microSDL_tsCollect  sCollect;             ///< Collection of elements on page
  
  int                 nPageId;              ///< Page identifier
  
  // Redraw
  bool                bPageNeedRedraw;      ///< Page require a redraw
  bool                bPageNeedFlip;        ///< Screen requires a page flip
} microSDL_tsPage;


/// GUI structure
/// - Contains all GUI state and content
/// - Maintains list of one or more pages
typedef struct {

  microSDL_tsFont*    asFont;           ///< Collection of loaded fonts
  unsigned            nFontMax;         ///< Maximum number of fonts to allocate
  unsigned            nFontCnt;         ///< Number of fonts allocated

  microSDL_tsElem     sElemTmp;         ///< Temporary element
  
  microSDL_tsView*    asView;           ///< Collection of viewports
  unsigned            nViewMax;         ///< Maximum number of viewports to allocate
  unsigned            nViewCnt;         ///< Number of viewports allocated
  int                 nViewIndCur;      ///< Currently-active viewport index

  int                 nTouchLastX;      ///< Last touch event X coord
  int                 nTouchLastY;      ///< Last touch event Y coord
  unsigned            nTouchLastPress;  ///< Last touch event pressure (0=none))

  // Touchscreen library interface
  #ifdef INC_TS
  struct tsdev*       ts;               ///< Ptr to touchscreen device
  #endif

 
  // Primary surface definitions
  void*               pvSurfScreen;     ///< Surface ptr for screen
  void*               pvSurfBkgnd;      ///< Surface ptr for background
  
  // Pages
  microSDL_tsPage*    asPage;           ///< Array of pages
  unsigned            nPageMax;         ///< Maximum number of pages
  unsigned            nPageCnt;         ///< Current page index
  
  microSDL_tsPage*    pCurPage;         ///< Currently active page
  microSDL_tsCollect* pCurPageCollect;  ///< Ptr to active page collection
  
} microSDL_tsGui;



// ------------------------------------------------------------------------
// General Functions
// ------------------------------------------------------------------------

///
/// Configure environment variables suitable for
/// default driver operations.
///
/// - NOTE: Users with other hardware may need to
///   supply their own initialization routine
///   as these defaults may not be suitable.
///
/// \param[in]  pGui:    Pointer to GUI
///
/// \return None
///
void microSDL_InitEnv(microSDL_tsGui* pGui);

///
/// Initialize the microSDL library
/// - Configures the primary screen surface
/// - Initializes font support
///
/// PRE:
/// - The environment variables should be configured before
///   calling microSDL_Init(). This can be done with microSDL_InitEnv()
///   or manually in user function.
///
/// POST:
/// - microSDL_m_surfScreen is initialized
///
/// \param[in]  pGui:      Pointer to GUI
/// \param[in]  asPage:    Pointer to Page array
/// \param[in]  nMaxPage:  Size of Page array
/// \param[in]  asFont:    Pointer to Font array
/// \param[in]  nMaxFont:  Size of Font array
/// \param[in]  asView:    Pointer to View array
/// \param[in]  nMaxView:  Size of View array
///
/// \return true if success, false if fail
///
bool microSDL_Init(microSDL_tsGui* pGui,microSDL_tsPage* asPage,unsigned nMaxPage,microSDL_tsFont* asFont,unsigned nMaxFont,microSDL_tsView* asView,unsigned nMaxView);




///
/// Exit the microSDL environment
/// - Calls SDL Quit to clean up any initialized subsystems
///   and also deletes any created elements or fonts
///
/// \param[in]  pGui:    Pointer to GUI
///
/// \return None
///
void microSDL_Quit(microSDL_tsGui* pGui);


///
/// Perform main microSDL handling functions
/// - Handles any touch events
/// - Performs any necessary screen redraw
///
/// \param[in]  pGui:    Pointer to GUI
///
/// \return None
///
void microSDL_Update(microSDL_tsGui* pGui);


// ------------------------------------------------------------------------
// Graphics General Functions
// ------------------------------------------------------------------------


///
/// Determine if a coordinate is inside of a rectangular region.
/// - This routine is useful in determining if a touch
///   coordinate is inside of a button.
///
/// \param[in]  nSelX:       X coordinate to test
/// \param[in]  nSelY:       X coordinate to test
/// \param[in]  rRect:       Rectangular region to compare against
///
/// \return true if inside region, false otherwise
///
bool microSDL_IsInRect(int nSelX,int nSelY,microSDL_Rect rRect);


///
/// Expand or contract a rectangle in width and/or height (equal
/// amounts on both side), based on the centerpoint of the rectangle.
///
/// \param[in]  rRect:       Rectangular region before resizing
/// \param[in]  nExpandW:    Number of pixels to expand the width (if positive)
///                          of contract the width (if negative)
/// \param[in]  nExpandH:    Number of pixels to expand the height (if positive)
///                          of contract the height (if negative)
///
/// \return microSDL_Rect() with resized dimensions
///
microSDL_Rect microSDL_ExpandRect(microSDL_Rect rRect,int16_t nExpandW,int16_t nExpandH);


///
/// Determine if a coordinate is inside of a width x height region.
/// - This routine is useful in determining if a relative coordinate
///   is within a given W x H dimension
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nSelX:       X coordinate to test
/// \param[in]  nSelY:       X coordinate to test
/// \param[in]  nWidth:      Width to test against
/// \param[in]  nHeight:     Height to test against
///
/// \return true if inside region, false otherwise
///
bool microSDL_IsInWH(microSDL_tsGui* pGui,int nSelX,int nSelY,uint16_t nWidth,uint16_t nHeight);




// ------------------------------------------------------------------------
// Graphics Primitive Functions
// - These routines cause immediate drawing to occur on the
//   primary screen
// ------------------------------------------------------------------------


///
/// Set a pixel on the active screen to the given color with lock
/// - Calls upon microSDL_DrvDrawSetPixelRaw() but wraps with a surface lock lock
/// - If repeated access is needed, use microSDL_DrvDrawSetPixelRaw() instead
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nX:          Pixel X coordinate to set
/// \param[in]  nY:          Pixel Y coordinate to set
/// \param[in]  nPixelCol:   Color pixel value ot assign
/// \param[in]  bMapEn:      Support viewport remapping
///
/// \return none
///
void microSDL_DrawSetPixel(microSDL_tsGui* pGui,int16_t nX,int16_t nY,microSDL_Color nCol,bool bMapEn);


///
/// Draw an arbitrary line using Bresenham's algorithm
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nX0:         X coordinate of line startpoint
/// \param[in]  nY0:         Y coordinate of line startpoint
/// \param[in]  nX1:         X coordinate of line endpoint
/// \param[in]  nY1:         Y coordinate of line endpoint
/// \param[in]  nCol:        Color RGB value for the line
///
/// \return none
///
void microSDL_DrawLine(microSDL_tsGui* pGui,int16_t nX0,int16_t nY0,int16_t nX1,int16_t nY1,microSDL_Color nCol);


///
/// Draw a horizontal line
/// - Note that direction of line is in +ve X axis
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nX:          X coordinate of line startpoint
/// \param[in]  nY:          Y coordinate of line startpoint
/// \param[in]  nW:          Width of line (in +X direction)
/// \param[in]  nCol:        Color RGB value for the line
///
/// \return none
///
void microSDL_DrawLineH(microSDL_tsGui* pGui,int16_t nX, int16_t nY, uint16_t nW,microSDL_Color nCol);


///
/// Draw a vertical line
/// - Note that direction of line is in +ve Y axis
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nX:          X coordinate of line startpoint
/// \param[in]  nY:          Y coordinate of line startpoint
/// \param[in]  nH:          Height of line (in +Y direction)
/// \param[in]  nCol:        Color RGB value for the line
///
/// \return none
///
void microSDL_DrawLineV(microSDL_tsGui* pGui,int16_t nX, int16_t nY, uint16_t nH,microSDL_Color nCol);


///
/// Draw a framed rectangle
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  rRect:       Rectangular region to frame
/// \param[in]  nCol:        Color RGB value for the frame
///
/// \return none
///
void microSDL_DrawFrameRect(microSDL_tsGui* pGui,microSDL_Rect rRect,microSDL_Color nCol);


///
/// Draw a filled rectangle
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  rRect:       Rectangular region to fill
/// \param[in]  nCol:        Color RGB value to fill
///
/// \return none
///
void microSDL_DrawFillRect(microSDL_tsGui* pGui,microSDL_Rect rRect,microSDL_Color nCol);

///
/// Draw a framed circle
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nMidX:       Center X coordinate
/// \param[in]  nMidY:       Center Y coordinate
/// \param[in]  nRadius:     Radius of circle
/// \param[in]  nCol:        Color RGB value for the frame
///
/// \return none
///
void microSDL_DrawFrameCircle(microSDL_tsGui* pGui,int16_t nMidX,int16_t nMidY,
  uint16_t nRadius,microSDL_Color nCol);



// -----------------------------------------------------------------------
// Font Functions
// -----------------------------------------------------------------------

///
/// Load a font into the local font cache and assign
/// font ID (nFontId).
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nFontId:     ID to use when referncing this font
/// \param[in]  acFontName:  Filename path to the font
/// \param[in]  nFontSz:     Typeface size to use
///
/// \return true if load was successful, false otherwise
///
bool microSDL_FontAdd(microSDL_tsGui* pGui,int nFontId, const char* acFontName, unsigned nFontSz);


///
/// Fetch a font from its ID value
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nFontId:     ID value used to reference the font (supplied
///                          originally to microSDL_FontAdd()
///
/// \return A void pointer to the font data or NULL if error
///         The type is defined by the driver.
///
void* microSDL_FontGet(microSDL_tsGui* pGui,int nFontId);




// ------------------------------------------------------------------------
// Page Functions
// ------------------------------------------------------------------------

///
/// Fetch the current page ID
///
/// \param[in]  pGui:        Pointer to GUI
///
/// \return Page ID
///

int microSDL_GetPageCur(microSDL_tsGui* pGui);


///
/// Select a new page for display
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nPageId:     Page ID to select as current
///
/// \return none
///
void microSDL_SetPageCur(microSDL_tsGui* pGui,int nPageId);


///
/// Update the need-redraw status for the current page
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  bRedraw:     True if redraw required, false otherwise
///
/// \return none
///
void microSDL_PageRedrawSet(microSDL_tsGui* pGui,bool bRedraw);


///
/// Get the need-redraw status for the current page
///
/// \param[in]  pGui:        Pointer to GUI
///
/// \return True if redraw required, false otherwise
///
bool microSDL_PageRedrawGet(microSDL_tsGui* pGui);


///
/// Redraw all elements on the active page. Only the
/// elements that have been marked as needing redraw are
/// rendered unless the entire page has been marked as
/// needing redraw (in which case everything is drawn)
///
/// \param[in]  pGui:        Pointer to GUI
///
/// \return none
///
void microSDL_PageRedrawGo(microSDL_tsGui* pGui);

///
/// Indicate whether the screen requires page flip
/// - This is generally called with bNeeded=true whenever
///   drawing has been done to the active page. Page flip
///   is actually performed later when calling PageFlipGo().
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  bNeeded:     True if screen requires page flip
///
/// \return None
///
void microSDL_PageFlipSet(microSDL_tsGui* pGui,bool bNeeded);


///
/// Get state of pending page flip state
///
/// \param[in]  pGui:        Pointer to GUI
///
/// \return True if screen requires page flip
///
bool microSDL_PageFlipGet(microSDL_tsGui* pGui);


///
/// Update the visible screen if page has been marked for flipping
/// - On some hardware this can trigger a double-buffering
///   page flip.
///
/// \param[in]  pGui:        Pointer to GUI
///
/// \return None
///
void microSDL_PageFlipGo(microSDL_tsGui* pGui);


/// Add a page to the GUI
/// - This call associates an element array with the collection within the page
/// - Once a page has been added to the GUI, elements can be added to the page
///   by specifying the same page ID
///
/// \param[in]  pGui:         Pointer to GUI
/// \param[in]  nPageId:      Page ID to assign
/// \param[in]  psElem:       Element array storage to associate with the page
/// \param[in]  nMaxElem:     Maximum number of elements that can be added to page
///
/// \return none
///
void microSDL_PageAdd(microSDL_tsGui* pGui,int nPageId,microSDL_tsElem* psElem,unsigned nMaxElem);

/// Find a page in the GUI by its ID
///
/// \param[in]  pGui:         Pointer to GUI
/// \param[in]  nPageId:      Page ID to search
///
/// \return Ptr to a page or NULL if none found
///
microSDL_tsPage* microSDL_PageFindById(microSDL_tsGui* pGui,int nPageId);

/// Find an element in the GUI by its Page ID and Element ID
///
/// \param[in]  pGui:         Pointer to GUI
/// \param[in]  nPageId:      Page ID to search
/// \param[in]  nElemId:      Element ID to search
///
/// \return Ptr to an element or NULL if none found
///
microSDL_tsElem* microSDL_PageFindElemById(microSDL_tsGui* pGui,int nPageId,int nElemId);

/// Perform a redraw calculation on the page to determine if additional
/// elements should also be redrawn. This routine checks to see if any
/// transparent elements have been marked as needing redraw. If so, the
/// whole page may be marked as needing redraw (or at least the other
/// elements that have been exposed underneath).
///
/// \param[in]  pGui:         Pointer to GUI
///
/// \return none
///
void microSDL_PageRedrawCalc(microSDL_tsGui* pGui);


// ------------------------------------------------------------------------
// Element Creation Functions
// ------------------------------------------------------------------------


///
/// Create a Text Element
/// - Draws a text string with filled background
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nElemId:     Element ID to assign (0..32767 or MSDL_ID_AUTO to autogen)
/// \param[in]  nPage:       Page ID to attach element to
/// \param[in]  rElem:       Rectangle coordinates defining text background size
/// \param[in]  pStr:        String to copy into element
/// \param[in]  nFontId:     Font ID to use for text display
///
/// \return Pointer to the Element or NULL if failure
///
microSDL_tsElem* microSDL_ElemCreateTxt(microSDL_tsGui* pGui,int nElemId,int nPage,
  microSDL_Rect rElem,const char* pStr,int nFontId);


///
/// Create a textual Button Element
/// - Creates a clickable element that has a textual label
///   with frame and fill
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nElemId:     Element ID to assign (0..32767 or MSDL_ID_AUTO to autogen)
/// \param[in]  nPage:       Page ID to attach element to
/// \param[in]  rElem:       Rectangle coordinates defining text background size
/// \param[in]  acStr:       String to copy into element
/// \param[in]  nFontId:     Font ID to use for text display
/// \param[in]  cbTouch:     Callback for touch events
///
/// \return Pointer to the Element or NULL if failure
///
microSDL_tsElem* microSDL_ElemCreateBtnTxt(microSDL_tsGui* pGui,int nElemId,int nPage,
  microSDL_Rect rElem,const char* acStr,int nFontId,MSDL_CB_TOUCH cbTouch);

///
/// Create a graphical Button Element
/// - Creates a clickable element that uses a BMP image with
///   no frame or fill
/// - Transparency is supported by bitmap color (0xFF00FF)
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nElemId:     Element ID to assign (0..32767 or MSDL_ID_AUTO to autogen)
/// \param[in]  nPage:       Page ID to attach element to
/// \param[in]  rElem:       Rectangle coordinates defining image size
/// \param[in]  acImg:       Filename of BMP image to load (unselected state)
/// \param[in]  acImgSel:    Filename of BMP image to load (selected state)
/// \param[in]  cbTouch:     Callback for touch events
///
/// \return Pointer to the Element or NULL if failure
///
microSDL_tsElem* microSDL_ElemCreateBtnImg(microSDL_tsGui* pGui,int nElemId,int nPage,
  microSDL_Rect rElem,const char* acImg,const char* acImgSel,MSDL_CB_TOUCH cbTouch);


///
/// Create a Box Element
/// - Draws a box with frame and fill
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nElemId:     Element ID to assign (0..32767 or MSDL_ID_AUTO to autogen)
/// \param[in]  nPage:       Page ID to attach element to
/// \param[in]  rElem:       Rectangle coordinates defining box size
///
/// \return Pointer to the Element or NULL if failure
///
microSDL_tsElem* microSDL_ElemCreateBox(microSDL_tsGui* pGui,int nElemId,int nPage,microSDL_Rect rElem);

///
/// Create an image Element
/// - Draws an image
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nElemId:     Element ID to assign (0..32767 or MSDL_ID_AUTO to autogen)
/// \param[in]  nPage:       Page ID to attach element to
/// \param[in]  rElem:       Rectangle coordinates defining box size
/// \param[in]  acImg:       Filename of BMP image to load
///
/// \return Pointer to the Element or NULL if failure
///
microSDL_tsElem* microSDL_ElemCreateImg(microSDL_tsGui* pGui,int nElemId,int nPage,microSDL_Rect rElem,
  const char* acImg);


// ------------------------------------------------------------------------
// Element Update Functions
// ------------------------------------------------------------------------


/// Get an Element ID from an element structure
///
/// \param[in]  pElem:       Pointer to element structure
///
/// \return ID of element or MSDL_ID_NONE if not found
///
int microSDL_ElemGetId(microSDL_tsElem* pElem);


///
/// Set the fill state for an Element
///
/// \param[in]  pElem:       Pointer to Element
/// \param[in]  bFillEn:     True if filled, false otherwise
///
/// \return none
///
void microSDL_ElemSetFillEn(microSDL_tsElem* pElem,bool bFillEn);

///
/// Update the common color selection for an Element
///
/// \param[in]  pElem:       Pointer to Element
/// \param[in]  colFrame:    Color for the frame
/// \param[in]  colFill:     Color for the fill
/// \param[in]  colGlow:     Color when glowing
///
/// \return none
///
void microSDL_ElemSetCol(microSDL_tsElem* pElem,microSDL_Color colFrame,microSDL_Color colFill,microSDL_Color colGlow);

///
/// Set the group ID for an element
/// - Typically used to associate radio button elements together
///
/// \param[in]  pElem:       Pointer to Element
/// \param[in]  nGroupId:    Group ID to assign
///
/// \return none
///
void microSDL_ElemSetGroup(microSDL_tsElem* pElem,int nGroupId);


///
/// Get the group ID for an element
///
/// \param[in]  pElem:       Pointer to Element
///
/// \return Group ID or MSDL_GROUP_ID_NONE if unassigned
///
int microSDL_ElemGetGroup(microSDL_tsElem* pElem);


/// Set the alignment of a textual element (horizontal and vertical)
///
/// \param[in]  pElem:       Pointer to Element
/// \param[in]  nAlign:      Alignment to specify:
///                           - MSDL_ALIGN_TOP_LEFT
///                           - MSDL_ALIGN_TOP_MID
///                           - MSDL_ALIGN_TOP_RIGHT
///                           - MSDL_ALIGN_MID_LEFT
///                           - MSDL_ALIGN_MID_MID
///                           - MSDL_ALIGN_MID_RIGHT
///                           - MSDL_ALIGN_BOT_LEFT
///                           - MSDL_ALIGN_BOT_MID
///                           - MSDL_ALIGN_BOT_RIGHT
///
/// \return none
///
void microSDL_ElemSetTxtAlign(microSDL_tsElem* pElem,unsigned nAlign);


///
/// Update the text string associated with an Element ID
///
/// \param[in]  pElem:       Pointer to Element
/// \param[in]  pStr:        String to copy into element
///
/// \return none
///
void microSDL_ElemSetTxtStr(microSDL_tsElem* pElem,const char* pStr);

///
/// Update the text string color associated with an Element ID
///
/// \param[in]  pElem:       Pointer to Element
/// \param[in]  colVal:      RGB color to change to
///
/// \return none
///
void microSDL_ElemSetTxtCol(microSDL_tsElem* pElem,microSDL_Color colVal);


///
/// Update the Font selected for an Element's text
///
/// \param[in]  pElem:       Pointer to Element
/// \param[in]  nFontId:     Font ID to select
///
/// \return none
///
void microSDL_ElemUpdateFont(microSDL_tsGui* pGui,microSDL_tsElem* pElem,int nFontId);

///
/// Update the need-redraw status for an element
///
/// \param[in]  pElem:       Pointer to Element
/// \param[in]  bRedraw:     True if redraw required, false otherwise
///
/// \return none
///
void microSDL_ElemSetRedraw(microSDL_tsElem* pElem,bool bRedraw);

///
/// Update the glowing enable for an element
///
/// \param[in]  pElem:      Pointer to Element
/// \param[in]  bGlowEn:    True if element should support glowing
///
/// \return none
///
void microSDL_ElemSetGlowEn(microSDL_tsElem* pElem,bool bGlowEn);


///
/// Get the glowing enable for an element
///
/// \param[in]  pElem:       Pointer to Element
///
/// \return True if element supports glowing
///
bool microSDL_ElemGetGlowEn(microSDL_tsElem* pElem);


///
/// Update the glowing indicator for an element
///
/// \param[in]  pElem:       Pointer to Element
/// \param[in]  bGlowing:    True if element is glowing
///
/// \return none
///
void microSDL_ElemSetGlow(microSDL_tsElem* pElem,bool bGlowing);


///
/// Get the glowing indicator for an element
///
/// \param[in]  pElem:       Pointer to Element
///
/// \return True if element is glowing
///
bool microSDL_ElemGetGlow(microSDL_tsElem* pElem);


///
/// Assign the drawing callback function for an element
/// - This allows the user to override the default rendering for
///   an element, enabling the creation of a custom element
///
/// \param[in]  pElem:       Pointer to Element
/// \param[in]  funcCb:      Function pointer to drawing routine (or NULL for default))
///
/// \return none
///
void microSDL_ElemSetDrawFunc(microSDL_tsElem* pElem,MSDL_CB_DRAW funcCb);

///
/// Assign the tick callback function for an element
/// - This allows the user to provide background updates to
///   an element triggered by the main loop call to microSDL_Update()
///
/// \param[in]  pElem:       Pointer to Element
/// \param[in]  funcCb:      Function pointer to tick routine (or NULL for none))
///
/// \return none
///
void microSDL_ElemSetTickFunc(microSDL_tsElem* pElem,MSDL_CB_TICK funcCb);



// ------------------------------------------------------------------------
// Element Drawing Functions
// ------------------------------------------------------------------------

///
/// Draw an element to the active display
/// - Element is referenced by a page ID and element ID
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nPageId:     ID of page containing element
/// \param[in]  nElemId:     ID of element
///
/// \return none
///
void microSDL_ElemDraw(microSDL_tsGui* pGui,int nPageId,int nElemId);



// ------------------------------------------------------------------------
// Viewport Functions
// ------------------------------------------------------------------------

///
/// Create a Viewport
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nViewId:     View ID to assign (0..32767)
/// \param[in]  rView:       Rectangle coordinates defining viewport position
/// \param[in]  nOriginX:    Relative X coordinates of origin
/// \param[in]  nOriginY:    Relative Y coordinates of origin
///
/// \return The Viewport ID or MSDL_VIEW_ID_NONE if failure
///
int microSDL_ViewCreate(microSDL_tsGui* pGui,int nViewId,microSDL_Rect rView,unsigned nOriginX,unsigned nOriginY);


///
/// Set the origin for a Viewport
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nViewId:     Viewport ID to update
/// \param[in]  nOriginX:    Relative X coordinates of origin
/// \param[in]  nOriginY:    Relative Y coordinates of origin
///
/// \return true if success, false if failure
///
bool microSDL_ViewSetOrigin(microSDL_tsGui* pGui,int nViewId,unsigned nOriginX,unsigned nOriginY);

///
/// Sets the currently active view
/// - This function is used to swap between drawing within
///   a viewport (using local coordinates and clipping) and
///   the main view (the screen).
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nViewId:     Viewport ID to select or MSDL_VIEW_ID_SCREEN for main display
///
/// \return none
///
void microSDL_ViewSet(microSDL_tsGui* pGui,int nViewId);


// ------------------------------------------------------------------------
// Element Collection Functions
// ------------------------------------------------------------------------


/// Reset the members of an element collection
///
/// \param[in]  pCollect:     Pointer to the collection
/// \param[in]  asElem:       Array of elements to associate with the collection
/// \param[in]  nElemMax:     Maximum number of element in the element array
///
/// \return none
/// 
void microSDL_CollectReset(microSDL_tsCollect* pCollect,microSDL_tsElem* asElem,unsigned nElemMax);


/// Add an element to a collection
/// - Note that the contents of pElem are copied to the collection's
///   element array so the pElem pointer can be discarded are the
///   call is complete.
///
/// \param[in]  pCollect:     Pointer to the collection
/// \param[in]  pElem:        Ptr to the element to add
///
/// \return Pointer to the element in the collection that has been added
///         or NULL if there was an error
/// 
microSDL_tsElem* microSDL_CollectElemAdd(microSDL_tsCollect* pCollect,microSDL_tsElem* pElem);


/// Find an element in a collection by its Element ID
///
/// \param[in]  pCollect:     Pointer to the collection
/// \param[in]  nElemId:      Element ID to search for
///
/// \return Pointer to the element in the collection that was found
///         or NULL if no matches found
/// 
microSDL_tsElem* microSDL_CollectFindElemById(microSDL_tsCollect* pCollect,int nElemId);


/// Find an element in a collection by a coordinate coordinate
/// - A match is found if the element is "clickable" (bClickEn=true)
///   and the coordinate falls within the element's bounds (rElem).
///
/// \param[in]  pCollect:     Pointer to the collection
/// \param[in]  nX:           Absolute X coordinate to use for search
/// \param[in]  nY:           Absolute Y coordinate to use for search
///
/// \return Pointer to the element in the collection that was found
///         or NULL if no matches found
/// 
microSDL_tsElem* microSDL_CollectFindElemFromCoord(microSDL_tsCollect* pCollect,int nX, int nY);


/// Allocate the next available Element ID in a collection
///
/// \param[in]  pCollect:     Pointer to the collection
///
/// \return Element ID that is reserved for use
/// 
int microSDL_CollectGetNextId(microSDL_tsCollect* pCollect);


/// Get the element within a collection that is currently being tracked
///
/// \param[in]  pCollect:     Pointer to the collection
///
/// \return Pointer to the element in the collection that is
///         currently being tracked or NULL if no elements
///         are being tracked
///
microSDL_tsElem* microSDL_CollectGetElemTracked(microSDL_tsCollect* pCollect);


/// Set the element within a collection that is currently being tracked
///
/// \param[in]  pCollect:     Pointer to the collection
/// \param[in]  pElem:        Ptr to element to mark as being tracked
///
/// \return none
///
void microSDL_CollectSetElemTracked(microSDL_tsCollect* pCollect,microSDL_tsElem* pElem);


/// Assign the parent element reference to all elements within a collection
/// - This is generally used in the case of compound elements where updates to
///   a sub-element should cause the parent (compound element) to be redrawn
///   as well.)
///
/// \param[in]  pCollect:     Pointer to the collection
/// \param[in]  pElemParent:  Ptr to element that is the parent
///
/// \return none
///
void microSDL_CollectSetParent(microSDL_tsCollect* pCollect,microSDL_tsElem* pElemParent);


/// Handle touch events within the element collection
///
/// \param[in]  pGui:         Pointer to the GUI
/// \param[in]  pCollect:     Ptr to the element collection
/// \param[in]  bTouchDown:   Touch event was a pressure applied (down)
/// \param[in]  bTouchUp:     Touch event was a pressure release (up)
/// \param[in]  bTouchMove:   Touch event was a movement with pressure
/// \param[in]  nX:           X coordinate of touch event
/// \param[in]  nY:           Y coordinate of touch event
///
/// \return none
///
void microSDL_CollectTouch(microSDL_tsGui* pGui,microSDL_tsCollect* pCollect,bool bTouchDown,bool bTouchUp,bool bTouchMove,int nX,int nY);


/// Handle redraw requests to the element collection
///
/// \param[in]  pGui:         Pointer to the GUI
/// \param[in]  pCollect:     Ptr to the element collection
/// \param[in]  bRedrawAll:   Force all element collection to be redrawn
///
/// \return none
///
void microSDL_CollectRedraw(microSDL_tsGui* pGui,microSDL_tsCollect* pCollect,bool bRedrawAll);


/// Handle tick events to the element collection
/// - This is callled from the GUI's microSDL_Update() call
///   and can be used to trigger background element activity
///
/// \param[in]  pGui:         Pointer to the GUI
/// \param[in]  pCollect:     Ptr to the element collection
///
/// \return none
///
void microSDL_CollectTick(microSDL_tsGui* pGui,microSDL_tsCollect* pCollect);


// ------------------------------------------------------------------------
// Tracking Functions
// ------------------------------------------------------------------------


///
/// Handles a touch event and performs the necessary
/// tracking, glowing and selection actions depending
/// on the press state.
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  pCollect:    Pointer to Element collection
/// \param[in]  nX:          X coordinate of touch event
/// \param[in]  nY:          Y coordinate of touch event
/// \param[in]  nPress:      Pressure level of touch event (0 for none, else touch)
///
/// \return none
///
void microSDL_TrackTouch(microSDL_tsGui* pGui,microSDL_tsCollect* pCollect,int nX,int nY,unsigned nPress);




// ------------------------------------------------------------------------
// Touchscreen Functions
// ------------------------------------------------------------------------

#ifdef INC_TS

///
/// Initialize the touchscreen device
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  acDev:       Device path to touchscreen
///                  eg. "/dev/input/touchscreen"
///
/// \return true if successful
///
bool microSDL_InitTs(microSDL_tsGui* pGui,const char* acDev);


///
/// Get the last touch event from the tslib handler
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[out] pnX:         Ptr to X coordinate of last touch event
/// \param[out] pnY:         Ptr to Y coordinate of last touch event
/// \param[out] pnPress:     Ptr to  Pressure level of last touch event (0 for none, >0 for touch)
///
/// \return non-zero if an event was detected or 0 otherwise
///
int microSDL_GetTsTouch(microSDL_tsGui* pGui,int* pnX, int* pnY, unsigned* pnPress);


#endif // INC_TS




// ------------------------------------------------------------------------
// Private Functions
// - The following functions are generally not required for
//   typical users of microSdl. However, for advanced usage
//   more direct access may be required.
// ------------------------------------------------------------------------


///
/// Create a new element with default styling
///
/// \param[in]  pGui:         Pointer to GUI
/// \param[in]  nElemId:      User-supplied ID for referencing this element
///                           (or MSDL_ID_AUTO to auto-generate)
/// \param[in]  nPageId:      The page ID on which this page should be associated
/// \param[in]  nType:        Enumeration that indicates the type of element
///                           that is requested for creation. The type adjusts
///                           the visual representation and default styling.
/// \param[in]  rElem:        Rectangle region framing the element
/// \param[in]  pStr:         Pointer to string for textual elements
/// \param[in]  nFontId:      Font ID for textual elements
///
/// \return Initialized structure
///
microSDL_tsElem microSDL_ElemCreate(microSDL_tsGui* pGui,int nElemId,int nPageId,microSDL_teType nType,
  microSDL_Rect rElem,const char* pStr,int nFontId);


///
/// Add the Element to the list of generated elements
/// in the GUI environment.
/// - NOTE: The content of pElem is copied so the pointer
///         can be released after the call.
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nPageId:     Page ID to add element to (MSDL_PAGE_NONE to skip in
///                          case of temporary creation for compound elements)
/// \param[in]  pElem:       Pointer to Element to add
///
/// \return Pointer to Element or NULL if fail
///
microSDL_tsElem* microSDL_ElemAdd(microSDL_tsGui* pGui,int nPageId,microSDL_tsElem* pElem);



///
/// Set an element to use a bitmap image
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  pElem:       Pointer to Element to update
/// \param[in]  acImage:     String of filename for image
/// \param[in]  acImageSel:  String of filename for image (selected)
///
/// \return none
///
void microSDL_ElemSetImage(microSDL_tsGui* pGui,microSDL_tsElem* pElem,const char* acImage,
  const char* acImageSel);

///
/// Configure the background to use a bitmap image
/// - The background is used when redrawing the entire page
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  pStrFname:   Filename to BMP file
///
/// \return true if success, false if fail
///
bool microSDL_SetBkgndImage(microSDL_tsGui* pGui,char* pStrFname);


///
/// Configure the background to use a solid color
/// - The background is used when redrawing the entire page
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nCol:        RGB Color to use
///
/// \return true if success, false if fail
///
bool microSDL_SetBkgndColor(microSDL_tsGui* pGui,microSDL_Color nCol);

/// Draw an element to the active display
/// - Element is referenced by an element pointer
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  pElem:       Ptr to Element to draw
///
/// \return true if success, false otherwise
///
bool microSDL_ElemDrawByRef(microSDL_tsGui* pGui,microSDL_tsElem* pElem);



///
/// Free up any surfaces associated with the GUI,
/// pages, collections and elements. Also frees
/// up any fonts.
/// - Called by microSDL_Quit()
/// 
/// \param[in]  pGui:         Pointer to GUI
/// 
/// \return none
///
void microSDL_GuiDestruct(microSDL_tsGui* pGui);


///
/// Free up any members associated with a page
/// 
/// \param[in]  pPage:        Pointer to Page
/// 
/// \return none
///
void microSDL_PageDestruct(microSDL_tsPage* pPage);

///
/// Free up any members associated with an element collection
/// 
/// \param[in]  pCollect:     Pointer to collection
/// 
/// \return none
///
void microSDL_CollectDestruct(microSDL_tsCollect* pCollect);

///
/// Free up any members associated with an element
/// 
/// \param[in]  pElem:        Pointer to element
/// 
/// \return none
///
void microSDL_ElemDestruct(microSDL_tsElem* pElem);

///
/// Perform range check on Viewport Index
/// - Range checking is done before View array access
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nViewInd:    Viewport index
///
/// \return true if index is in range, false otherwise
///
bool microSDL_ViewIndValid(microSDL_tsGui* pGui,int nViewInd);

///
/// Look up the Viewport Index from the Viewport ID
///
/// \param[in]  pGui:        Pointer to GUI
/// \param[in]  nViewId:     ID of the viewport to find
///
/// \return Index of viewport or MSDL_VIEW_IND_NONE if not found
///
int microSDL_ViewFindIndFromId(microSDL_tsGui* pGui,int nViewId);

///
/// Remap a coordinate from local to global using the
/// viewport settings. The input coordinates will be
/// replaced by the global coordinates.
///
/// \param[in]    pGui:        Pointer to GUI
/// \param[in]    nViewId:     ID of the viewport
/// \param[inout] pnX:         Ptr to X coordinate
/// \param[inout] pnY:         Ptr to Y coordinate
///
/// \return none
///
void microSDL_ViewRemapPt(microSDL_tsGui* pGui,int16_t* pnX,int16_t* pnY);

///
/// Remap a rectangle from local to global using the
/// viewport settings. The input rectangle coordinates will be
/// replaced by the global coordinates.
///
/// \param[in]    pGui:        Pointer to GUI
/// \param[in]    nViewId:     ID of the viewport
/// \param[inout] prRect:      Ptr to Rectangular coordinates to update
///
/// \return none
///
void microSDL_ViewRemapRect(microSDL_tsGui* pGui,microSDL_Rect* prRect);


///
/// Notify an element of a touch event. This is an optional
/// behavior useful in some extended element types.
///
/// \param[in]  pGui:       Pointer to GUI
/// \param[in]  pElem:      Pointer to Element
/// \param[in]  eTouch:     Touch event type
/// \param[in]  nX:         X coordinate of event (absolute coordinate)
/// \param[in]  nY:         Y coordinate of event (absolute coordinate)
///
/// \return true if success, false if error
///
bool microSDL_NotifyElemTouch(microSDL_tsGui* pGui,microSDL_tsElem* pElem,
        microSDL_teTouch eTouch,int nX,int nY);


///
/// Initialize a Font struct
///
/// \param[in]  pFont:       Pointer to Font
///
/// \return none
///
void microSDL_ResetFont(microSDL_tsFont* pFont);

///
/// Initialize an Element struct
///
/// \param[in]  pElem:       Pointer to Element
///
/// \return none
///
void microSDL_ResetElem(microSDL_tsElem* pElem);

///
/// Initialize a View struct
///
/// \param[in]  pView:       Pointer to Viewport
///
/// \return none
///
void microSDL_ResetView(microSDL_tsView* pView);




// =======================




#ifdef __cplusplus
}
#endif // __cplusplus
#endif // _MICROSDL_H_