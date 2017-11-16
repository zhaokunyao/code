import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Collections;  


/**
 * Warehouse
 *
 * warehouse as a square (n x n) array of rooms
 *
 * @version 1.0
 */
public class Warehouse {
    /**
     *  roomList
     *
     * the rooms in the Warehouse
     *
     */
    private List<Room> roomList;

    /**
     * the height or width of the warehouse
     *
     * (size x size)
     *
     */
    private int size;

    /**
     * Warehouse
     *
     * constructor
     *
     * @access public
     * @param int 
     */
    public Warehouse(int size) {
        super();
        this.size = size;
        this.roomList = new ArrayList<Room>(size*size);
        // add size * size rooms. 
        // all room without door.
        for(int i = 0; i < size * size; i++) {
            this.roomList.add(new Room());
        }
    }

    public List<Room> getRoomList() {
        return roomList;
    }

    /**
     * install
     *
     * randomly give each room some doors
     *
     * @access public
     */
    public void install(){
        // if it is a 1x1 warehouse,  all the walls are external wall,
        // we can not install doors.
        if (this.size == 1) {
            return;
        }

        // loop and install each room
        for(int i=0;i<this.roomList.size();i++){
            this.installOneRoom(i);
        }
    }

    /**
     * isExternalWall
     *
     * calculate if it is a external wall
     *
     * @access private
     * @param int
     * @param string
     * @return bool
     */
    private boolean isExternalWall(int index, String wall) {
        // note: the index start from 0 , end with this.size*this.size-1
        // north wall with room index [0, this.size-1]
        if (index < this.size && wall == "north") {
            return true;
        }
        // south wall with room index [this.size * (this.size-1), this.size * this.size-1]
        if (index >= this.size * (this.size - 1) && wall == "south") {
            return true;
        }
        // west wall with room index: 0, this.size, this.size*2,  this.size*3 etc
        if (index % this.size == 0 && wall == "west") {
            return true;
        }
        // east wall with room index this.size-1, this.size*2-1, this.size*3-1 etc
        if (index % this.size == this.size - 1 && wall == "east") {
            return true;
        }
        // not external
        return false;
    }

    /**
     * installOneRoom
     *
     * randomly give one room some doors
     *
     * @access private
     * @param int 
     */
    private void installOneRoom(int index) {
        // System.out.print("install " + index + "\n");
        // get the room
        Room room = this.roomList.get(index);

        // get all the walls without door of the room
        List<String> wallList = room.wallsWithoutDoor();

        // remove external walls from wallList
        for (int i = wallList.size() - 1; i >= 0; i--) {
            String wall = wallList.get(i);
            if (this.isExternalWall(index, wall)) {
                // System.out.print("remove " + wall + "\n");
                wallList.remove(i);
            }
        }

        // loop until the room have no less than 2 doors
        while (room.getDoorCount() < 2) {
            // System.out.println("room have door count: " + room.getDoorCount());
            // shuffle the wallList
            Collections.shuffle(wallList);
            int i = 0;

            // get the first wall from wallList
            String wall = wallList.get(i);

            // ask the room the install door on the wall
            room.installDoor(wall);

            // get neighbour's wall according to room's wall.
            String neighbour_wall = this.getNeightbourWall(wall);

            // get neightbour room
            Room neighbour_room = this.getNeightbourRoom(index, wall);

            // neighbour_room install door.
            neighbour_room.installDoor(neighbour_wall);

            // remove the wall from wallList, cause it always have a door.
            wallList.remove(i);
        }
    }

    /**
     * getNeightbourWall
     *
     * get neighbour's wall according to room's wall
     *
     * @access private
     * @param string
     * @return string
     */
    private String getNeightbourWall(String wall) {
        if (wall == "north") {
            return  "south";
        }
        if (wall == "east") {
            return  "west";
        }
        if (wall == "south") {
            return  "north";
        }
        return  "east";
    }

    /**
     * getNeightbourRoom
     *
     * getNeightbourRoom according to current room's index and it's wall
     *
     * @access private
     * @param int
     * @param Room
     */
    private Room getNeightbourRoom(int index, String wall) {
        int neighbour_index;
        if (wall == "north") {
            // the line above 
            neighbour_index = index - this.size;
        } else if (wall == "east") {
            // right
            neighbour_index = index + 1;
        } else if (wall == "south") {
            // the line below
            neighbour_index = index + this.size;
        } else {
            // left
            neighbour_index = index - 1;
        }
        Room room = this.roomList.get(neighbour_index);
        return room;
    }

    /**
     * print
     *
     * draw the floorplan of the warehouse,
     *
     * @access public
     */
    public void print(){
        // loop each row.
        for(int i = 0; i < this.size; i++){
            // we have five component parts of each room.
            List<String> output_nwall = new ArrayList<String>();
            List<String> output_side = new ArrayList<String>();
            List<String> output_ewwall = new ArrayList<String>();
            List<String> output_side2 = new ArrayList<String>();
            List<String> output_swall = new ArrayList<String>();

            // loop each room in the row
            for (int j = 0; j < this.size; j++) {
                // calculate room's index
                int index = i * this.size + j;

                // get room
                Room room = this.roomList.get(index);
                // string representation
                String str_room = room.toString();
                // breaking string into component parts
                List<String> tokens = Arrays.asList(str_room.split("\n"));
                // save earch parts
                output_nwall.add(tokens.get(0));
                output_side.add(tokens.get(1));
                output_ewwall.add(tokens.get(2));
                output_side2.add(tokens.get(3));
                output_swall.add(tokens.get(4));
            }

            // output each room's top parts
            for (int j = 0; j < this.size; j++) {
                System.out.print(output_nwall.get(j));
            }
            System.out.print("\n");

            // output each room's inner_1 parts
            for (int j = 0; j < this.size; j++) {
                System.out.print(output_side.get(j));
            }

            // output each room's inner_2 parts
            System.out.print("\n");
            for (int j = 0; j < this.size; j++) {
                System.out.print(output_ewwall.get(j));
            }
            System.out.print("\n");

            // output each room's inner_3 parts
            for (int j = 0; j < this.size; j++) {
                System.out.print(output_side2.get(j));
            }
            System.out.print("\n");

            // output each room's bottom parts
            for (int j = 0; j < this.size; j++) {
                System.out.print(output_swall.get(j));
            }
            System.out.print("\n");
        }
    }
}
