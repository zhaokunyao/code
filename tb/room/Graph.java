

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Graph {
	
	public static void main(String[] args){
		List<Room> roomList = new ArrayList<Room>();
		int num = 6;
		for(int i=0;i<num*num;i++){
			Room room = new Room();
			if(i<num){
				//第一行,nWall不允许有door.
				room.setnWallCanDoor(false);
			}
			if(i%num==0){
				//第一列,wWall不允许有door
				room.setwWallCanDoor(false);
			}
			if(i>=(num*(num-1))){
				//最后一行,sWall不允许有door
				room.setsWallCanDoor(false);
			}
			if((i+1)%num==0){
				//最后一列,eWall不允许有door
				room.seteWallCanDoor(false);
			}
			roomList.add(room);
		}
		//设置门
		setBatchRoomDoor(roomList,num);
		//输出阵型图
		printRooms(roomList,num);
		//打印指定房间的门
		int row=2;
		int col=3;
		int roomIndex = (row-1)*num+col-1;
		Room targetRoom = roomList.get(roomIndex);
		String doorStr = row+"排"+col+"列";
		if(targetRoom.getnWall().contains("D")){
			doorStr += "\t north has door. \n";
		}
		if(targetRoom.getEwWall().startsWith("D")){
			doorStr += "\t west has door. \n";
		}
		if(targetRoom.getsWall().contains("D")){
			doorStr += "\t south has door. \n";
		}
		if(targetRoom.getEwWall().endsWith("D")){
			doorStr += "\t east has door. \n";
		}
		System.out.println(doorStr);
	}
	
	/**
	 * 设置门
	 */
	private static void setBatchRoomDoor(List<Room> roomList,int num){
		for(int i=0;i<roomList.size();i++){
			Room room = roomList.get(i);
			if(room.getDoorCount()<2 && room.getCanSetDoorCount()>0){
				setSingleRoomDoor(room,i,num,roomList);
			}
		}
	}
	
	private static void setSingleRoomDoor(Room room,int roomIndex,int num,List<Room> roomList){
		int canSetDoorCount = room.getCanSetDoorCount();
		//还有几个需要设置门的
		int needSetDoor = 2-room.getDoorCount();
		List<Integer> setDoorIndex = getRandomArrayFromArray(needSetDoor,canSetDoorCount);
		int canSetDoorIndex = 0;
		//
		if(room.iseWallCanDoor()){
			if(setDoorIndex.contains(canSetDoorIndex)){
				// eWall需设置门
				room.seteWallCanDoor(false);
				String eWall = room.getEwWall().replace("   |", "   D");
				room.setEwWall(eWall);
				
				//右边的房子
				Room rightRoom = roomList.get(roomIndex+1);
				rightRoom.setwWallCanDoor(false);
				String wWall = rightRoom.getEwWall().replace("|   ", "D   ");
				rightRoom.setEwWall(wWall);
			}
			canSetDoorIndex++;
		}
		
		if(room.issWallCanDoor()){
			if(setDoorIndex.contains(canSetDoorIndex)){
				// sWall需设置门
				room.setsWallCanDoor(false);
				String sWall = room.getsWall().replace("-----", "--D--");
				room.setsWall(sWall);
				
				// 下边的房子
				Room downRoom = roomList.get(roomIndex+num);
				downRoom.setnWallCanDoor(false);
				String nWall = downRoom.getnWall().replace("-----", "--D--");
				downRoom.setnWall(nWall);
			}
			canSetDoorIndex++;
		}
		
		if(room.iswWallCanDoor()){
			if(setDoorIndex.contains(canSetDoorIndex)){
				// wWall需设置门
				room.setwWallCanDoor(false);
				String ewWall = room.getEwWall().replace("|   ", "D   ");
				room.setEwWall(ewWall);
				
				// 左边的房子
				Room leftRoom = roomList.get(roomIndex-1);
				leftRoom.seteWallCanDoor(false);
				String eWall = leftRoom.getEwWall().replace("   |", "   D");
				leftRoom.setEwWall(eWall);
			}
			canSetDoorIndex++;
		}
		
		if(room.isnWallCanDoor()){
			if(setDoorIndex.contains(canSetDoorIndex)){
				// nWall需设置门
				room.setnWallCanDoor(false);
				String nWall = room.getnWall().replace("-----", "--D--");
				room.setnWall(nWall);
				
				// 上边的房子
				Room upRoom = roomList.get(roomIndex-num);
				upRoom.setsWallCanDoor(false);
				String sWall = upRoom.getsWall().replace("-----", "--D--");
				upRoom.setsWall(sWall);
			}
		}
//		}
	}
	
	private static List<Integer> getRandomArrayFromArray(int needArraysSize,int options){
		List<Integer> result = new ArrayList<Integer>();
		Random radom = new Random();
		while(true){
			int index = radom.nextInt(options);
			if(!result.contains(index)){
				result.add(index);
				
				if(result.size()==needArraysSize){
					break;
				}
			}
		}
		
		return result;
	}
	
	
	/**
	 * 输出房间
	 * @param roomList
	 * @param num
	 */
	private static void printRooms(List<Room> roomList,int num){
		for(int i=0;i<num;i++){
			for(int j=0;j<num;j++){
				System.out.print(roomList.get(i*num+j).getnWall());
			}
			System.out.print("\n");
			for(int j=0;j<num;j++){
				System.out.print(roomList.get(i*num+j).getSide());
			}
			System.out.print("\n");
			for(int j=0;j<num;j++){
				System.out.print(roomList.get(i*num+j).getEwWall());
			}
			System.out.print("\n");
			for(int j=0;j<num;j++){
				System.out.print(roomList.get(i*num+j).getSide());
			}
			System.out.print("\n");
			for(int j=0;j<num;j++){
				System.out.print(roomList.get(i*num+j).getsWall());
			}
			System.out.print("\n");
		}
	}
}
