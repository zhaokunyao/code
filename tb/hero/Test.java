import java.util.ArrayList;
import java.util.List;

public class Test {

    private static void testRoomInit() {
        Room room = new Room();
        List<String> wallList = new ArrayList<String>();

        int doorCount = room.getDoorCount();
        assert doorCount==0;
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
        int doorCount = room.getDoorCount();
        assert doorCount == 1;
        wallList = room.wallsWithoutDoor();
        assert wallList.contains("north");
        assert wallList.contains("south");
        assert wallList.contains("west");
        assert (!wallList.contains("east"));

        room.installDoor("west");
        doorCount = room.getDoorCount();
        assert doorCount == 2;
        wallList = room.wallsWithoutDoor();
        assert wallList.contains("north");
        assert wallList.contains("south");
        assert (!wallList.contains("west"));
        assert (!wallList.contains("east"));

        room.installDoor("south");
        doorCount = room.getDoorCount();
        assert doorCount == 3;
        wallList = room.wallsWithoutDoor();
        assert wallList.contains("north");
        assert (!wallList.contains("south"));
        assert (!wallList.contains("west"));
        assert (!wallList.contains("east"));

        room.installDoor("north");
        doorCount = room.getDoorCount();
        assert doorCount == 4;
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
        int doorCount = room.getDoorCount();
        assert doorCount == 1;
        wallList = room.wallsWithoutDoor();
        assert wallList.contains("north");
        assert wallList.contains("south");
        assert wallList.contains("west");
        assert (!wallList.contains("east"));

        room.installDoor("east");
        doorCount = room.getDoorCount();
        assert doorCount == 1;
        wallList = room.wallsWithoutDoor();
        assert wallList.contains("north");
        assert wallList.contains("south");
        assert wallList.contains("west");
        assert (!wallList.contains("east"));

        room.installDoor("east");
        doorCount = room.getDoorCount();
        assert doorCount == 1;
        wallList = room.wallsWithoutDoor();
        assert wallList.contains("north");
        assert wallList.contains("south");
        assert wallList.contains("west");
        assert (!wallList.contains("east"));
    }
    private static void testWarehouseZeroRoom() {
        Warehouse w = new Warehouse(0);
        List<Room> roomList = new ArrayList<Room>();
        roomList = w.getRoomList();
        assert roomList.size() == 0;
        System.out.println("should print nothing.");
        w.print();
    }
    private static void testWarehouseOneRoom() {
        Warehouse w = new Warehouse(1);
        List<Room> roomList = new ArrayList<Room>();
        roomList = w.getRoomList();
        assert roomList.size() == 1;
        w.install();
        System.out.println("should print an room without door.");
        w.print();
    }

    private static void testWarehouseInit() {
        // loop
        for (int size = 2; size < 100; size ++) {
            // just init. do not install
            Warehouse w = new Warehouse(size);
            List<Room> roomList = new ArrayList<Room>();
            roomList = w.getRoomList();
            assert roomList.size() == size * size;
            int doorCount = 0;
            for (Room room : roomList) {
                doorCount += room.getDoorCount();
            }
            assert doorCount == 0;
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
            List<Room> roomList = new ArrayList<Room>();
            roomList = w.getRoomList();
            for (int i = 0; i < roomList.size(); i++) {
                Room room = roomList.get(i);
                int doorCount = room.getDoorCount();
                // door count in each room:  >=2 and <= 4 
                assert(doorCount >=2 && doorCount <= 4);

                // assert external walls do not have doors.
                List<String> wallList = new ArrayList<String>();
                wallList = room.wallsWithoutDoor();
                if (i < size) {
                    assert wallList.contains("north");
                }
                if (i >= size * (size - 1)) {
                    assert wallList.contains("south");
                }
                if (i % size == 0) {
                    assert wallList.contains("west");
                }
                if (i % size == size - 1) {
                    assert wallList.contains("east");
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

    private static void testItem() {
        Item item = new Item();
        item.setSize(10);
        item.setValue(20);
        item.setName("ELF");

        assert 10 == item.getSize();
        assert 20 == item.getValue();
        assert "ELF" == item.getName();
    }

    private static void testHero() {
        List<Item> itemList = new ArrayList<Item>();
        Hero hero = new Hero();
        itemList = hero.getItemList();
        assert itemList.size() == 0;

        Item item = new Item();
        item.setSize(10);
        item.setValue(20);
        item.setName("ELF");

        assert hero.pickUp(item);

        itemList = hero.getItemList();
        assert itemList.size() == 1;
        assert 10 == itemList.get(0).getSize();
        assert 20 == itemList.get(0).getValue();
        assert "ELF" == itemList.get(0).getName();

        // add a new item with smaller size
        Item item2 = new Item();
        item2.setSize(7);
        item2.setValue(14);
        item2.setName("MOON");

        assert hero.pickUp(item2);

        itemList = hero.getItemList();
        assert itemList.size() == 2;
        assert 7 == itemList.get(0).getSize();
        assert 14 == itemList.get(0).getValue();
        assert "MOON" == itemList.get(0).getName();
        assert 10 == itemList.get(1).getSize();
        assert 20 == itemList.get(1).getValue();
        assert "ELF" == itemList.get(1).getName();

        // add a new item with bigger size
        Item item3 = new Item();
        item3.setSize(30);
        item3.setValue(2);
        item3.setName("SUN");

        assert hero.pickUp(item3);
        itemList = hero.getItemList();
        assert itemList.size() == 3;
        assert 7 == itemList.get(0).getSize();
        assert 14 == itemList.get(0).getValue();
        assert "MOON" == itemList.get(0).getName();
        assert 10 == itemList.get(1).getSize();
        assert 20 == itemList.get(1).getValue();
        assert "ELF" == itemList.get(1).getName();
        assert 30 == itemList.get(2).getSize();
        assert 2 == itemList.get(2).getValue();
        assert "SUN" == itemList.get(2).getName();

        // add a new item up to 50 size
        Item item4 = new Item();
        item4.setSize(3);
        item4.setValue(4);
        item4.setName("EARTH");
        assert hero.pickUp(item4);
        itemList = hero.getItemList();
        assert itemList.size() == 4;
        assert 3 == itemList.get(0).getSize();
        assert 4 == itemList.get(0).getValue();
        assert "EARTH" == itemList.get(0).getName();
        assert 7 == itemList.get(1).getSize();
        assert 14 == itemList.get(1).getValue();
        assert "MOON" == itemList.get(1).getName();
        assert 10 == itemList.get(2).getSize();
        assert 20 == itemList.get(2).getValue();
        assert "ELF" == itemList.get(2).getName();
        assert 30 == itemList.get(3).getSize();
        assert 2 == itemList.get(3).getValue();
        assert "SUN" == itemList.get(3).getName();

        // add a new item beyond 50 size
        Item item5 = new Item();
        item5.setSize(1);
        item5.setValue(1);
        item5.setName("MERCURY");
        assert (!hero.pickUp(item5));
        itemList = hero.getItemList();
        assert itemList.size() == 4;
        assert 3 == itemList.get(0).getSize();
        assert 4 == itemList.get(0).getValue();
        assert "EARTH" == itemList.get(0).getName();
        assert 7 == itemList.get(1).getSize();
        assert 14 == itemList.get(1).getValue();
        assert "MOON" == itemList.get(1).getName();
        assert 10 == itemList.get(2).getSize();
        assert 20 == itemList.get(2).getValue();
        assert "ELF" == itemList.get(2).getName();
        assert 30 == itemList.get(3).getSize();
        assert 2 == itemList.get(3).getValue();
        assert "SUN" == itemList.get(3).getName();

        // drop a  item
        hero.drop(item4);
        itemList = hero.getItemList();
        assert itemList.size() == 3;
        assert 7 == itemList.get(0).getSize();
        assert 14 == itemList.get(0).getValue();
        assert "MOON" == itemList.get(0).getName();
        assert 10 == itemList.get(1).getSize();
        assert 20 == itemList.get(1).getValue();
        assert "ELF" == itemList.get(1).getName();
        assert 30 == itemList.get(2).getSize();
        assert 2 == itemList.get(2).getValue();
        assert "SUN" == itemList.get(2).getName();
        hero.drop(item3);
        itemList = hero.getItemList();
        assert itemList.size() == 2;
        assert 7 == itemList.get(0).getSize();
        assert 14 == itemList.get(0).getValue();
        assert "MOON" == itemList.get(0).getName();
        assert 10 == itemList.get(1).getSize();
        assert 20 == itemList.get(1).getValue();
        assert "ELF" == itemList.get(1).getName();
        hero.drop(item2);
        itemList = hero.getItemList();
        assert itemList.size() == 1;
        assert 10 == itemList.get(0).getSize();
        assert 20 == itemList.get(0).getValue();
        assert "ELF" == itemList.get(0).getName();
        hero.drop(item);
        itemList = hero.getItemList();
        assert itemList.size() == 0;

    }

    private static void testWarehouseInstallHero() {
        Warehouse warehouse = new Warehouse(8);
        Hero hero = new Hero();
        warehouse.installHero(hero);
        int heroPos = warehouse.getHeroPos();
        assert(heroPos >= 0 && heroPos < 8*8);
    }

    private static void testWarehouseMoveHero() {
        Warehouse warehouse = new Warehouse(8);
        warehouse.install();
        Hero hero = new Hero();
        warehouse.installHero(hero);

        int oldHeroPos = warehouse.getHeroPos();
        Room room = warehouse.getRoomList().get(oldHeroPos);
        for (int i = 0; i < 10; i++) {
            if (!room.isnWallHadDoor()) {
                warehouse.moveHero("n");
                // move failed
                assert oldHeroPos == warehouse.getHeroPos();
                oldHeroPos = warehouse.getHeroPos();
                room = warehouse.getRoomList().get(oldHeroPos);
            }
            if (!room.iseWallHadDoor()) {
                warehouse.moveHero("e");
                // move failed
                assert oldHeroPos == warehouse.getHeroPos();
                oldHeroPos = warehouse.getHeroPos();
                room = warehouse.getRoomList().get(oldHeroPos);
            }
            if (!room.issWallHadDoor()) {
                warehouse.moveHero("s");
                // move failed
                assert oldHeroPos == warehouse.getHeroPos();
                oldHeroPos = warehouse.getHeroPos();
                room = warehouse.getRoomList().get(oldHeroPos);
            }
            if (!room.iswWallHadDoor()) {
                warehouse.moveHero("w");
                // move failed
                assert oldHeroPos == warehouse.getHeroPos();
                oldHeroPos = warehouse.getHeroPos();
                room = warehouse.getRoomList().get(oldHeroPos);
            }
            if (room.isnWallHadDoor()) {
                warehouse.moveHero("n");
                // move success
                assert oldHeroPos == warehouse.getHeroPos() + 8;
                oldHeroPos = warehouse.getHeroPos();
                room = warehouse.getRoomList().get(oldHeroPos);
                continue;
            }
            if (room.iseWallHadDoor()) {
                warehouse.moveHero("e");
                // move success
                assert oldHeroPos == warehouse.getHeroPos() - 1;
                oldHeroPos = warehouse.getHeroPos();
                room = warehouse.getRoomList().get(oldHeroPos);
                continue;
            }
            if (room.issWallHadDoor()) {
                warehouse.moveHero("s");
                // move success
                assert oldHeroPos == warehouse.getHeroPos() - 8;
                oldHeroPos = warehouse.getHeroPos();
                room = warehouse.getRoomList().get(oldHeroPos);
                continue;
            }
            if (room.iswWallHadDoor()) {
                warehouse.moveHero("w");
                // move success
                assert oldHeroPos == warehouse.getHeroPos() + 1;
                oldHeroPos = warehouse.getHeroPos();
                room = warehouse.getRoomList().get(oldHeroPos);
                continue;
            }
        }
    }

    private static void testWarehouseDoDropTransaction() {
        Warehouse warehouse = new Warehouse(8);
        Hero hero = new Hero();
        List<Item> itemList = new ArrayList<Item>();
        Item item1 = new Item();
        item1.setSize(1);
        itemList.add(item1);
        Item item2 = new Item();
        item2.setSize(2);
        itemList.add(item2);
        Item item3 = new Item();
        item3.setSize(3);
        itemList.add(item3);
        warehouse.installHero(hero);
        int heroPos = warehouse.getHeroPos();
        Room room = warehouse.getRoomList().get(heroPos);
        hero.pickUp(item1);
        hero.pickUp(item2);
        hero.pickUp(item3);

        warehouse.doDropTransaction(item1);
        assert(hero.getItemList().size() == 2);
        assert(room.getItemList().size() == 1 && room.getItemList().get(0).getSize() == 1);
        warehouse.doDropTransaction(item2);
        assert(hero.getItemList().size() == 1);
        assert(room.getItemList().size() == 2 && room.getItemList().get(0).getSize() == 1
            && room.getItemList().get(1).getSize() == 2);
        warehouse.doDropTransaction(item3);
        assert(hero.getItemList().size() == 0);
        assert(room.getItemList().size() == 3 && room.getItemList().get(0).getSize() == 1
            && room.getItemList().get(1).getSize() == 2
            && room.getItemList().get(2).getSize() == 3);
    }

    private static void testWarehouseDoPickupTransaction() {
        Warehouse warehouse = new Warehouse(8);
        Hero hero = new Hero();
        List<Item> itemList = new ArrayList<Item>();
        Item item1 = new Item();
        item1.setSize(10);
        itemList.add(item1);
        Item item2 = new Item();
        item2.setSize(20);
        itemList.add(item2);
        Item item3 = new Item();
        item3.setSize(30);
        itemList.add(item3);
        warehouse.installHero(hero);
        int heroPos = warehouse.getHeroPos();
        Room room = warehouse.getRoomList().get(heroPos);
        room.addItem(item1);
        room.addItem(item2);
        room.addItem(item3);

        warehouse.doPickupTransaction(item1);
        assert(room.getItemList().size() == 2);
        assert(hero.getItemList().size() == 1 && hero.getItemList().get(0).getSize() == 10);

        warehouse.doPickupTransaction(item2);
        assert(room.getItemList().size() == 1);
        assert(hero.getItemList().size() == 2 && hero.getItemList().get(0).getSize() == 10
            && hero.getItemList().get(1).getSize() == 20);

        // beyond max capcity
        warehouse.doPickupTransaction(item3);
        assert(room.getItemList().size() == 1);
        assert(hero.getItemList().size() == 2 && hero.getItemList().get(0).getSize() == 10
            && hero.getItemList().get(1).getSize() == 20);
    }

    private static void testWarehouseInstallItems() {
        Warehouse warehouse = new Warehouse(8);
        List<Item> itemList = new ArrayList<Item>();
        List<Item> itemList2 = new ArrayList<Item>();
        Item item1 = new Item();
        item1.setSize(1);
        itemList.add(item1);
        Item item2 = new Item();
        item2.setSize(2);
        itemList.add(item2);
        Item item3 = new Item();
        item3.setSize(3);
        itemList.add(item3);
        warehouse.installItems(itemList);

        List<Room> roomList = warehouse.getRoomList();
        int size = 0;
        for (Room room : roomList) {
            List<Item> roomItemList = room.getItemList();
            for (Item it : roomItemList) {
                itemList2.add(it);
                size += it.getSize();
            }
        }
        assert itemList2.size() == 3;
        assert size == 6;
    }

    public static void main(String[] args) {
        // test room
        testRoomInit();
        testRoomInstallDoor();
        testRoomInstallDuplicateDoor();

        // test item
        testItem();

        // test hero
        testHero();

        // test warehouse
        testWarehouseZeroRoom();
        testWarehouseOneRoom();
        testWarehouseInit();
        testWarehouseInstallItems();
        testWarehouseInstallHero();
        testWarehouseMoveHero();
        testWarehouseDoDropTransaction();
        testWarehouseDoPickupTransaction();
        testWarehouseInstall();
    }
}
