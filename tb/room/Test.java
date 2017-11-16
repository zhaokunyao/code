
public class Test {

	public static void main(String[] args){
		int num=5;
		Warehouse wareHouse = new Warehouse(num);
		//输出warehouse的房间图
		wareHouse.printRooms();
		int row = 3;
		int col = 4;
		int roomIndex = (row-1)*num+col-1;
		Room targetRoom = wareHouse.getRoomList().get(roomIndex);
		if(targetRoom!=null){
			targetRoom.print();
		}
	}
}
