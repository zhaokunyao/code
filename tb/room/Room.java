

public class Room {
	private String side = "|   |";
	private String nWall = "-----";
	private String sWall = "-----";
	private String ewWall = side;
	
	private boolean eWallCanDoor = true;
	private boolean sWallCanDoor = true;
	private boolean wWallCanDoor = true;
	private boolean nWallCanDoor = true;
	public String getSide() {
		return side;
	}
	public void setSide(String side) {
		this.side = side;
	}
	public String getnWall() {
		return nWall;
	}
	public void setnWall(String nWall) {
		this.nWall = nWall;
	}
	public String getsWall() {
		return sWall;
	}
	public void setsWall(String sWall) {
		this.sWall = sWall;
	}
	public String getEwWall() {
		return ewWall;
	}
	public void setEwWall(String ewWall) {
		this.ewWall = ewWall;
	}
	@Override
	public String toString() {
		return nWall+"\n"+side+"\n"+ewWall+"\n"+side+"\n"+sWall;
	}
	
	/**
	 * 已设置门个数
	 * @return
	 */
	public int getDoorCount(){
		int doorCount = 0;
		if(nWall.contains("D")){
			doorCount++;
		}
		if(sWall.contains("D")){
			doorCount++;
		}
		if(ewWall.contains("D")){
			doorCount += ewWall.length() - ewWall.replaceAll("D","").length();
		}
		return doorCount;
	}
	
	/**
	 * 能设置门个数
	 * @return
	 */
	public int getCanSetDoorCount(){
		int canSetDoorCount = 0;
		if(eWallCanDoor){
			canSetDoorCount++;
		}
		if(sWallCanDoor){
			canSetDoorCount++;
		}
		if(wWallCanDoor){
			canSetDoorCount++;
		}
		if(nWallCanDoor){
			canSetDoorCount++;
		}
		return canSetDoorCount;
	}
	
	public boolean iseWallCanDoor() {
		return eWallCanDoor;
	}
	public void seteWallCanDoor(boolean eWallCanDoor) {
		this.eWallCanDoor = eWallCanDoor;
	}
	public boolean issWallCanDoor() {
		return sWallCanDoor;
	}
	public void setsWallCanDoor(boolean sWallCanDoor) {
		this.sWallCanDoor = sWallCanDoor;
	}
	public boolean iswWallCanDoor() {
		return wWallCanDoor;
	}
	public void setwWallCanDoor(boolean wWallCanDoor) {
		this.wWallCanDoor = wWallCanDoor;
	}
	public boolean isnWallCanDoor() {
		return nWallCanDoor;
	}
	public void setnWallCanDoor(boolean nWallCanDoor) {
		this.nWallCanDoor = nWallCanDoor;
	}
}
