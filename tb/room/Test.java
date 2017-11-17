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
        System.out.println("should print an room without door.");
        w.print();
        w.install();
        System.out.println("should print an room without door.");
        w.print();
    }

    private static void testWarehouseInit() {
        Warehouse w = new Warehouse(2);
        List<Room> room_list = new ArrayList<Room>();
        room_list = w.getRoomList();
        assert room_list.size() == 2 * 2;
        System.out.println("should print 2x2 rooms without door.");
        w.print();
        int door_count = 0;
        for (Room room : room_list) {
            door_count += room.getDoorCount();
        }
        assert door_count == 0;

        w = new Warehouse(10);
        room_list = w.getRoomList();
        assert room_list.size() == 10 * 10;
        System.out.println("should print 10x10 rooms without door.");
        w.print();
        door_count = 0;
        for (Room room : room_list) {
            door_count += room.getDoorCount();
        }
        assert door_count == 0;
    }

    private static void testWarehouseInstall() {
    }

    public static void main(String[] args){
        testRoomInit();
        testRoomInstallDoor();
        testRoomInstallDuplicateDoor();
        testWarehouseZeroRoom();
        testWarehouseOneRoom();
        testWarehouseInit();
        testWarehouseInstall();
    }
}
