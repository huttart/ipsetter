#define UP_BTN      0
#define RIGHT_BTN   1
#define DOWN_BTN    2
#define LEFT_BTN    3
#define CENTER_BTN  4

#define FONT_SIZE   6
#define FONT_HEIGHT 10
int APP_STATE = 0;
int STATE_DIAGRAM[20][5] = {/* u,r,d,l,c  */          /*|---------------------------------------------------|*/
                              {0,0,1,0,0},            /*|  State = 0  | Initial state.                      |*/
                              {0,1,1,1,2},            /*|  State = 1  | Focusing on SET-IP button.          |*/
                              {2,3,2,2,14},           /*|  State = 2  | Focusing setting ip at position 1   |*/
                              {3,4,3,2,14},           /*|  State = 3  | Focusing setting ip at position 2   |*/
                              {4,5,4,3,14},           /*|  State = 4  | Focusing setting ip at position 3   |*/
                              {5,6,5,4,14},           /*|  State = 5  | Focusing setting ip at position 4   |*/
                              {6,7,6,5,14},           /*|  State = 6  | Focusing setting ip at position 5   |*/
                              {7,8,7,6,14},           /*|  State = 7  | Focusing setting ip at position 6   |*/
                              {8,9,8,7,14},           /*|  State = 8  | Focusing setting ip at position 7   |*/
                              {9,10,9,8,14},          /*|  State = 9  | Focusing setting ip at position 8   |*/
                              {10,11,10,9,14},        /*|  State = 10 | Focusing setting ip at position 9   |*/
                              {11,12,11,10,14},       /*|  State = 11 | Focusing setting ip at position 10  |*/
                              {12,13,12,11,14},       /*|  State = 12 | Focusing setting ip at position 11  |*/
                              {13,14,13,12,14},       /*|  State = 13 | Focusing setting ip at position 12  |*/
                              {13,15,14,14,0},        /*|  State = 14 | Focusing CANCEL button.             |*/
                              {13,15,15,14,16},       /*|  State = 15 | Focusing OK button.                 |*/
                           };                         /*|---------------------------------------------------|*/
