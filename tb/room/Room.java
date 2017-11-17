import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * Room
 *
 * room with wall, wall with door.
 *
 * @version 1.0
 */
public class Room {
    /**
     * side
     *
     */
    private String side = "|   |";

    /**
     * nWall
     *
     * top
     *
     */
    private String nWall = "-----";

    /**
     * sWall
     *
     * bottom
     *
     */
    private String sWall = "-----";

    /**
     * ewWall
     *
     * (east and west wall)
     *
     */
    private String ewWall = side;

    /**
     * Room
     *
     * constructor
     *
     * @access public
     */
    public Room() {
        super();
    }

    /**
     * getter and setter
     */
    private String getnWall() {
        return nWall;
    }
    private void setnWall(String nWall) {
        this.nWall = nWall;
    }
    private String getsWall() {
        return sWall;
    }
    private void setsWall(String sWall) {
        this.sWall = sWall;
    }
    private String getEwWall() {
        return ewWall;
    }
    private void setEwWall(String ewWall) {
        this.ewWall = ewWall;
    }

    /**
     * iseWallHadDoor
     *
     * if east wall have door.
     *
     * @access private
     * @return boolean
     */
    private boolean iseWallHadDoor() {
        return this.ewWall.endsWith("D");
    }
    private boolean issWallHadDoor() {
        return this.sWall.contains("D");
    }
    private boolean iswWallHadDoor() {
        return this.ewWall.startsWith("D");
    }
    private boolean isnWallHadDoor() {
        return this.nWall.contains("D");
    }

    @Override
    public String toString() {
        return nWall+"\n"+side+"\n"+ewWall+"\n"+side+"\n"+sWall;
    }

    /**
     * getDoorCount
     *
     * return the total door count of the room.
     *
     * @access public
     * @return int
     */
    public int getDoorCount(){
        int doorCount = 0;
        if (this.iseWallHadDoor()) {
            doorCount ++;
        }
        if (this.iswWallHadDoor()) {
            doorCount ++;
        }
        if (this.issWallHadDoor()) {
            doorCount ++;
        }
        if (this.isnWallHadDoor()) {
            doorCount ++;
        }
        return doorCount;
    }

    /**
     * print
     *
     * print a room
     *
     * @access public
     */
    public void print(){
        System.out.println("You are in a room.");
        if (this.isnWallHadDoor()) {
            System.out.println("There is a door going north");
        }
        if (this.iswWallHadDoor()){
            System.out.println("There is a door going west");
        }
        if (this.issWallHadDoor()) {
            System.out.println("There is a door going south");
        }
        if (this.iseWallHadDoor()) {
            System.out.println("There is a door going east");
        }
    }

    /**
     * wallsWithDoor
     *
     * return all the walls with a door of the room.
     *
     * @access public
     * @return List<String>
     */
    public List<String> wallsWithDoor() {
        List<String> wallList = new ArrayList<String>();
        if (this.isnWallHadDoor()) {
            wallList.add("north");
        }
        if (this.issWallHadDoor()) {
            wallList.add("south");
        }
        if (this.iseWallHadDoor()) {
            wallList.add("east");
        }
        if (this.iswWallHadDoor()) {
            wallList.add("west");
        }
        return wallList;
    }

    /**
     * wallsWithoutDoor
     *
     * return all the walls without a door of the room.
     *
     * @access public
     * @return List<String>
     */
    public List<String> wallsWithoutDoor() {
        List<String> wallList = new ArrayList<String>();
        if (!this.isnWallHadDoor()) {
            wallList.add("north");
        }
        if (!this.issWallHadDoor()) {
            wallList.add("south");
        }
        if (!this.iseWallHadDoor()) {
            wallList.add("east");
        }
        if (!this.iswWallHadDoor()) {
            wallList.add("west");
        }
        return wallList;
    }

    /**
     * installDoor
     *
     * install a door on the wall
     *
     * @access public
     * @param String
     */
    public void installDoor(String wall) {
        // System.out.println("room install " + wall);
        if (wall == "north") {
            String s = this.getnWall().replace("-----", "--D--");
            this.setnWall(s);
            return;
        }
        if (wall == "south") {
            String s = this.getsWall().replace("-----", "--D--");
            this.setsWall(s);
            return;
        }
        if (wall == "east") {
            String s = this.getEwWall().replace("   |", "   D");
            this.setEwWall(s);
            return;
        }
        if (wall == "west") {
            String s = this.getEwWall().replace("|   ", "D   ");
            this.setEwWall(s);
            return;
        }
    }
}
