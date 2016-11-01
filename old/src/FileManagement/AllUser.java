package FileManagement;

import java.util.Hashtable;

public class AllUser {
	private String username;
	private Hashtable<String, MyDir> userlist = new Hashtable<String, MyDir>();
    private static AllUser inst=new AllUser();
	private AllUser(){
		
	}
	public static synchronized AllUser getInstance(){
		return inst;
	}
	
	public void addUser(MyDir a) {
		this.userlist.put(a.getName(), a);
	}
	
	public boolean whetherExist(String username){
		return userlist.containsKey(username);
	}
    public MyDir getUserDir(String username){
    	return this.userlist.get(username);
    }
	public String getUsername() {
		return username;
	}

	public void setUsername(String username) {
		this.username = username;
	}

	public Hashtable<String, MyDir> getUserlist() {
		return userlist;
	}

	public void setUserlist(Hashtable<String, MyDir> userlist) {
		this.userlist = userlist;
	}
}


