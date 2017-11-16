import java.util.Scanner;

/**
 * Graph
 *
 * user interface and the main.
 *
 * @version 1.0
 */
public class Graph {

    /**
     * main
     *
     * the main function.
     *
     * @access public
     * @param string[]
     */
    public static void main(String[] args){
        Scanner scn = new Scanner(System.in);
        System.out.print("Please enter the size of the warehouse: ");
        // parse user's input
        int num = Integer.parseInt(scn.nextLine());

        // create a warehouse as a square (n x n) array of rooms
        // with no doors in any of the rooms
        Warehouse wareHouse = new Warehouse(num);

        // randomly give each room some doors
        wareHouse.install();

        // draw the floorplan of the warehouse, 
        // indicating the position of each door.
        wareHouse.print();

        // ask the user to enter a starting position for the game
        // number each row and column from 1
        int[] position=inputPosition(scn,num);
        int row = position[0];
        int col = position[1];
        // calculate room index
        int roomIndex = (row-1)*num+col-1;
        // get the room from warehouse
        Room room = wareHouse.getRoomList().get(roomIndex);
        if(room !=null){
            // describe that room to the user.
            room.print();
        }
    }

    /**
     * inputPosition
     *
     * ask the user to enter a starting position for the game
     *
     * @access private static
     * @param Scanner
     * @param int 
     * @return int[]
     */
    private static int[] inputPosition(Scanner scn,int size){
        int[] position = new int[2];

        System.out.print("Enter starting position (row col): ");
        // parse user's input
        String inputStr = scn.nextLine();
        if(inputStr==null 
                || inputStr.trim()==null 
                || !inputStr.trim().contains(" ")
                || inputStr.trim().split(" ").length!=2){
            // bad input format
            System.out.println("Enter right position (row col). Like 2 3: ");
            // ask user to input again.
            return inputPosition(scn,size);
        }

        try{
            // split and parse row & col
            String[] splitStr = inputStr.trim().split(" ");
            int row = Integer.parseInt(splitStr[0]);
            int col = Integer.parseInt(splitStr[1]);

            if(row<1 || row>size || col<1 || col>size){
                // too small or too large
                System.out.println("you are not in a room.");
                // ask the user to input again.
                return inputPosition(scn,size);
            }
            position[0]=row;
            position[1]=col;
            return position;
        }catch(Exception e){
            System.out.println("Enter two int numbers.");
            // got exception  while parse
            // ask the user to input again.
            return inputPosition(scn,size);
        }
    }
}
