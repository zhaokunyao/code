import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

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

    private List<Item> itemList = new LinkedList<Item>();

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
     * iseWallHadDoor
     *
     * if east wall have door.
     *
     * @access private
     * @return boolean
     */
    public boolean iseWallHadDoor() {
        return this.ewWall.endsWith("D");
    }
    public boolean issWallHadDoor() {
        return this.sWall.contains("D");
    }
    public boolean iswWallHadDoor() {
        return this.ewWall.startsWith("D");
    }
    public boolean isnWallHadDoor() {
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
    public void print() {
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
        if(itemList.size()>0){
            for(int i=0;i<itemList.size();i++){
                Item item = itemList.get(i);
                System.out.println("There is a "+item.getName()+" here (size "+item.getSize()+", value "+item.getValue()+")");
            }
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
     * add item to room
     * @param item
     */
    public void addItem(Item item){
        this.itemList.add(item);
    }

    /**
     * remove item from room
     * @param item
     */
    public void removeItem(Item item){
        this.itemList.remove(item);
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
            String s = this.nWall.replace("-----", "--D--");
            this.nWall = s;
            return;
        }
        if (wall == "south") {
            String s = this.sWall.replace("-----", "--D--");
            this.sWall = s;
            return;
        }
        if (wall == "east") {
            String s = this.ewWall.replace("   |", "   D");
            this.ewWall = s;
            return;
        }
        if (wall == "west") {
            String s = this.ewWall.replace("|   ", "D   ");
            this.ewWall = s;
            return;
        }
    }

    public List<Item> getItemList() {
        return itemList;
    }
}
