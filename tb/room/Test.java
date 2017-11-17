import java.util.ArrayList;
import java.util.List;

public class Test {

    private static void testRoomInit() {
        Room room = new Room();
        List<String> wallList = new ArrayList<String>();

        int door_count = room.getDoorCount();
        assert door_count==0;
        wallList = room.wallsWithoutDoor();
        assert wallList.contains("north");
        assert wallList.contains("south");
        assert wallList.contains("west");
        assert wallList.contains("east");
    }

    private static void testRoomInstallDoor() {
        Room room = new Room();
        List<String> wallList = new ArrayList<String>();

        room.installDoor("east");
        int door_count = room.getDoorCount();
        assert door_count == 1;
        wallList = room.wallsWithoutDoor();
        assert wallList.contains("north");
        assert wallList.contains("south");
        assert wallList.contains("west");
        assert (!wallList.contains("east"));

        room.installDoor("west");
        door_count = room.getDoorCount();
        assert door_count == 2;
        wallList = room.wallsWithoutDoor();
        assert wallList.contains("north");
        assert wallList.contains("south");
        assert (!wallList.contains("west"));
        assert (!wallList.contains("east"));

        room.installDoor("south");
        door_count = room.getDoorCount();
        assert door_count == 3;
        wallList = room.wallsWithoutDoor();
        assert wallList.contains("north");
        assert (!wallList.contains("south"));
        assert (!wallList.contains("west"));
        assert (!wallList.contains("east"));

        room.installDoor("north");
        door_count = room.getDoorCount();
        assert door_count == 4;
        wallList = room.wallsWithoutDoor();
        assert (!wallList.contains("north"));
        assert (!wallList.contains("south"));
        assert (!wallList.contains("west"));
        assert (!wallList.contains("east"));
    }

    private static void testRoomInstallDuplicateDoor() {
        Room room = new Room();
        List<String> wallList = new ArrayList<String>();

        room.installDoor("east");
        int door_count = room.getDoorCount();
        assert door_count == 1;
        wallList = room.wallsWithoutDoor();
        assert wallList.contains("north");
        assert wallList.contains("south");
        assert wallList.contains("west");
        assert (!wallList.contains("east"));

        room.installDoor("east");
        door_count = room.getDoorCount();
        assert door_count == 1;
        wallList = room.wallsWithoutDoor();
        assert wallList.contains("north");
        assert wallList.contains("south");
        assert wallList.contains("west");
        assert (!wallList.contains("east"));

        room.installDoor("east");
        door_count = room.getDoorCount();
        assert door_count == 1;
        wallList = room.wallsWithoutDoor();
        assert wallList.contains("north");
        assert wallList.contains("south");
        assert wallList.contains("west");
        assert (!wallList.contains("east"));
    }
    private static void testWarehouseZeroRoom() {
        Warehouse w = new Warehouse(0);
        List<Room> room_list = new ArrayList<Room>();
        room_list = w.getRoomList();
        assert room_list.size() == 0;
        System.out.println("should print nothing.");
        w.print();
    }
    private static void testWarehouseOneRoom() {
        Warehouse w = new Warehouse(1);
        List<Room> room_list = new ArrayList<Room>();
        room_list = w.getRoomList();
        assert room_list.size() == 1;
        w.install();
        System.out.println("should print an room without door.");
        w.print();
    }

    private static void testWarehouseInit() {
        // loop
        for (int size = 2; size < 100; size ++) {
            // just init. do not install
            Warehouse w = new Warehouse(size);
            List<Room> room_list = new ArrayList<Room>();
            room_list = w.getRoomList();
            assert room_list.size() == size * size;
            int door_count = 0;
            for (Room room : room_list) {
                door_count += room.getDoorCount();
            }
            assert door_count == 0;
        }
    }

    private static void testWarehouseInstall() {
        // loop 
        for (int size = 2; size < 100; size ++) {
            Warehouse w = new Warehouse(size);
            
            // open trace.
            w.setTrace(true);

            // install
            w.install();

            // get room list
            List<Room> room_list = new ArrayList<Room>();
            room_list = w.getRoomList();
            for (int i = 0; i < room_list.size(); i++) {
                Room room = room_list.get(i);
                int door_count = room.getDoorCount();
                // door count in each room:  >=2 and <= 4 
                assert(door_count >=2 && door_count <= 4);

                // assert external walls do not have doors.
                List<String> wall_list = new ArrayList<String>();
                wall_list = room.wallsWithoutDoor();
                if (i < size) {
                    assert wall_list.contains("north");
                }
                if (i >= size * (size - 1)) {
                    assert wall_list.contains("south");
                }
                if (i % size == 0) {
                    assert wall_list.contains("west");
                }
                if (i % size == size - 1) {
                    assert wall_list.contains("east");
                }
            }
        }
    }

    /**
     * isNeightbourRoom
     *
     * is two rooms are neighbour
     *
     * @access private
     * @param int
     * @param int
     * @param int
     * @return boolean
     */
    private static boolean isNeightbourRoom(int index1, int index2, int size) {
        if (index1 == index2 - size) {
            return true;
        }
        if (index1 == index2 + size) {
            return true;
        }
        if ((index1 == index2 + 1) && (index1 % size != 0)) {
            return true;
        }
        if (index2 == index1 + 1 && (index2 % size != 0)) {
            return true;
        }
        return false;
    }

    /**
     * isNeighbourWall
     *
     * neighbour walls must be opposite;
     *
     * @access private
     * @param String
     * @param String
     * @return boolean
     */
    private static boolean isNeighbourWall(String w1, String w2) {
        if (w1 == "north") {
            return w2 == "south";
        }
        if (w1 == "south") {
            return w2 == "north";
        }
        if (w1 == "east") {
            return w2 == "west";
        }
        if (w1 == "west") {
            return w2 == "east";
        }
        return false;
    }

    public static void main(String[] args) {
        // test room
        testRoomInit();
        testRoomInstallDoor();
        testRoomInstallDuplicateDoor();

        // test warehouse
        testWarehouseZeroRoom();
        testWarehouseOneRoom();
        testWarehouseInit();
        testWarehouseInstall();
    }
}
