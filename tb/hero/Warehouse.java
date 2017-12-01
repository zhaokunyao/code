import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;


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
     * traceSwitch
     *
     * default is false
     *
     * @access private
     */
    private boolean traceSwitch;

    /**
     * hero
     *
     * @access private
     */
    private Hero hero;

    /**
     * heroPos
     */
    private int heroPos;

    public Hero getHero() {
        return hero;
    }

    public int getHeroPos() {
        return heroPos;
    }

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

        this.traceSwitch = false;
    }

    public List<Room> getRoomList() {
        return roomList;
    }

    public void setTrace(boolean onOff) {
        this.traceSwitch  = onOff;
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

        if (this.traceSwitch) {
            System.out.println("before install");
            this.print();
            try {
                TimeUnit.SECONDS.sleep(2);
            } catch (InterruptedException e) {
            }
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
            String neighbourWall = this.getNeightbourWall(wall);

            // get neightbour room
            Room neighbourRoom = this.getNeightbourRoom(index, wall);

            // neighbourRoom install door.
            neighbourRoom.installDoor(neighbourWall);

            // remove the wall from wallList, cause it always have a door.
            wallList.remove(i);

            // print trace log

            if (this.traceSwitch) {
                System.out.println("after install one door in one room and one door in the neighbour room");
                this.print();
                try {
                    TimeUnit.SECONDS.sleep(2);
                } catch (InterruptedException e) {
                }
            }

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
        int neighbourIndex;
        if (wall == "north") {
            // the line above 
            neighbourIndex = index - this.size;
        } else if (wall == "east") {
            // right
            neighbourIndex = index + 1;
        } else if (wall == "south") {
            // the line below
            neighbourIndex = index + this.size;
        } else {
            // left
            neighbourIndex = index - 1;
        }
        Room room = this.roomList.get(neighbourIndex);
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
            List<String> outputNwall = new ArrayList<String>();
            List<String> outputSide = new ArrayList<String>();
            List<String> outputEwwall = new ArrayList<String>();
            List<String> outputSide2 = new ArrayList<String>();
            List<String> outputSwall = new ArrayList<String>();

            // loop each room in the row
            for (int j = 0; j < this.size; j++) {
                // calculate room's index
                int index = i * this.size + j;

                // get room
                Room room = this.roomList.get(index);
                // string representation
                String strRoom = room.toString();
                // breaking string into component parts
                List<String> tokens = Arrays.asList(strRoom.split("\n"));
                // save earch parts
                outputNwall.add(tokens.get(0));
                outputSide.add(tokens.get(1));
                outputEwwall.add(tokens.get(2));
                outputSide2.add(tokens.get(3));
                outputSwall.add(tokens.get(4));
            }

            // output each room's top parts
            for (int j = 0; j < this.size; j++) {
                System.out.print(outputNwall.get(j));
            }
            System.out.print("\n");

            // output each room's inner 1 parts
            for (int j = 0; j < this.size; j++) {
                System.out.print(outputSide.get(j));
            }

            // output each room's inner 2 parts
            System.out.print("\n");
            for (int j = 0; j < this.size; j++) {
                System.out.print(outputEwwall.get(j));
            }
            System.out.print("\n");

            // output each room's inner 3 parts
            for (int j = 0; j < this.size; j++) {
                System.out.print(outputSide2.get(j));
            }
            System.out.print("\n");

            // output each room's bottom parts
            for (int j = 0; j < this.size; j++) {
                System.out.print(outputSwall.get(j));
            }
            System.out.print("\n");
        }
    }

    /**
     * random install hero
     */
    public void installHero(Hero hero){
        this.hero = hero;
        Random r = new Random();
        // make hero pos
        this.heroPos = r.nextInt(size*size);

        // get the room from warehouse
        Room room = this.getRoomList().get(heroPos);

        // describe that room to the user.
        System.out.println("You are in room ("+(this.heroPos / this.size + 1)
            + "," + (this.heroPos % this.size + 1)+")");
        room.print();
    }

    /**
     * handleCmdI
     *
     * print all the items in hero's backpack
     *
     * @access private
     */
    private void handleCmdI() {
        if (hero.getItemList().size()>0){
            System.out.println("Here are the items in your backpack:");
            for(int i=0;i<hero.getItemList().size();i++){
                System.out.println((i+1)+":"+hero.getItemList().get(i).print());
            }
        }else{
            System.out.println("Your backpack is empty.");
        }
    }

    /**
     * handleCmdP
     *
     * pick up
     *
     * @access private
     * @param Scanner
     */
    private void handleCmdP(Scanner scn) {
        Room room = this.getRoomList().get(heroPos);
        if(room.getItemList()!=null && room.getItemList().size()>0){
            System.out.println("OK. Here are the items you can pick up:");
            for(int i=0;i<room.getItemList().size();i++){
                System.out.println((i+1)+":"+room.getItemList().get(i).print());
            }
            System.out.print("Which item would you like?");
            int itemIndex = 0;
            try {
                itemIndex = Integer.parseInt(scn.nextLine());
            } catch(NumberFormatException e){
                itemIndex = -1;
            }
            if(itemIndex>0 && itemIndex<=room.getItemList().size()){
                Item item = room.getItemList().get(itemIndex-1);
                if (! this.doPickupTransaction(item)) {
                    System.out.println("not enough space left in your backpack");
                }
            }else{
                System.out.println("Your operate is not allowed");
            }
        }else{
            System.out.println("No items you can pick up");
        }

    }

    /**
     * doPickupTransaction
     *
     * in case of pick up failed, do not remove item from room 
     *
     * @access public
     * @param item
     * @return boolean
     */
    public boolean doPickupTransaction(Item item) {
        Room room = this.getRoomList().get(heroPos);
        if (this.hero.pickUp(item)) {
            room.removeItem(item);
            return true;
        }
        return false;
    }

    /**
     * handleCmdD
     *
     * drop 
     *
     * @access private
     * @param Scanner
     */
    private void handleCmdD(Scanner scn) {
        Room room = this.getRoomList().get(heroPos);
        if(this.hero.getItemList()!=null && this.hero.getItemList().size()>0){
            System.out.println("OK. Here are the items you can drop:");
            for(int i=0;i<this.hero.getItemList().size();i++){
                System.out.println((i+1)+":"+this.hero.getItemList().get(i).print());
            }
            System.out.print("Which item would you like?");
            int itemIndex = 0;
            try {
                itemIndex = Integer.parseInt(scn.nextLine());
            } catch(NumberFormatException e){
                itemIndex = -1;
            }
            if(itemIndex>0 && itemIndex<=this.hero.getItemList().size()){
                Item item = this.hero.getItemList().get(itemIndex-1);
                this.doDropTransaction(item);
            }else{
                System.out.println("Your operate is not allowed");
            }
        }else{
            System.out.println("No items you can drop");
        }
    }

    /**
     * doDropTransaction
     *
     *
     * @access public
     * @param item
     * @return boolean
     */
    public boolean doDropTransaction(Item item) {
        this.hero.drop(item);
        Room room = this.getRoomList().get(heroPos);
        room.addItem(item);
        return true;
    }

    /**
     * start the  game.
     */
    public void startGame() {
        Scanner scn = new Scanner(System.in);
        while(true){
            System.out.println();
            System.out.print("What would you like to do?");
            String command = scn.nextLine();
            System.out.println();
            if(command.equals("i")){
                this.handleCmdI();
            } else if(command.equals("p")){
                this.handleCmdP(scn);
            }else if(command.equals("d")){
                this.handleCmdD(scn);
            }else if(command.equals("n") || command.equals("e") || command.equals("w") || command.equals("s")){
                this.moveHero(command);
            }else{
                System.out.println("unknown cmd");
            }
        }
    }

    /**
     * go next room by direction
     * @param direction
     */
    public void moveHero(String direction){
        int newRoomIndex = this.heroPos;
        Room room = this.roomList.get(newRoomIndex);
        if(direction.equals("n")){
            //go north
            if(room.isnWallHadDoor()){
                newRoomIndex = this.heroPos-this.size;
            }
        }
        if(direction.equals("e")){
            //go east
            if(room.iseWallHadDoor()){
                newRoomIndex = this.heroPos+1;
            }
        }
        if(direction.equals("w")){
            //go west
            if(room.iswWallHadDoor()){
                newRoomIndex = this.heroPos-1;
            }
        }
        if(direction.equals("s")){
            //go south
            if(room.issWallHadDoor()){
                newRoomIndex = this.heroPos+this.size;
            }
        }

        if(newRoomIndex != this.heroPos){
            this.heroPos = newRoomIndex;
            //move success
            room=this.getRoomList().get(newRoomIndex);
            System.out.println("You are in room ("+(this.heroPos / this.size + 1)
                + "," + (this.heroPos % this.size + 1)+")");
            room.print();
        }else{
            System.out.println("You can't go that way.");
        }
    }

    /**
     * installItems
     *
     * random set items  to rooms
     *
     * @access public
     * @param List<Item>
     */
    public void installItems(List<Item> itemList) {
        //random set items to room.
        Random r = new Random();
        for(Item item : itemList){
            int itemToRoomIndex = r.nextInt(this.size * this.size);
            this.getRoomList().get(itemToRoomIndex).addItem(item);
        }
    }

}
