package FileManagement;

import java.io.Serializable;
import java.util.Hashtable;
import java.util.Iterator;

public class MyDisk implements Serializable{

	private static final long serialVersionUID = 1L;
	private static MyDisk a = new MyDisk();
	private Hashtable<Integer,MyDiskBlock> usedlist;
	private int restNum = 100;
	
	/**  当前磁盘块指针，只增不减，以防磁盘块冲突     */
	private int nowpoint=0;        

	private MyDisk() {
		this.usedlist = new Hashtable<Integer,MyDiskBlock>();
	}

	// 运用单例模式得到当前磁盘实例
	public static synchronized MyDisk getInstance() {
		return a;
	}

	

	public Hashtable<Integer, MyDiskBlock> getUsedlist() {
		return usedlist;
	}

	public void setUsedlist(Hashtable<Integer, MyDiskBlock> usedlist) {
		this.usedlist = usedlist;
	}

	public int getRestNum() {
		return restNum;
	}

	public void setRestNum(int restNum) {
		this.restNum = restNum;
	}

	
	//将某一个磁盘块上的内容保存到磁盘上
	public void addUsed(MyDiskBlock a){
		a.setId(nowpoint);
		this.usedlist.put(nowpoint,a);
		this.restNum--;
		this.nowpoint++;
	}
	
	//将指定盘块上的内容从磁块上删除
	public void deleteUsed(int a){
		this.usedlist.remove(a);
		this.restNum++;
	}
	
  // 打印已经使用过的磁盘块号
	public void showUsed() {
		System.out.println("--------------以下为已经使用的磁盘块号--------------");
		Iterator<Integer> it=usedlist.keySet().iterator();
		while(it.hasNext()) {
			System.out.print(usedlist.get(it.next()).getId() + "     ");
		}
		if (usedlist.size() > 0)
			System.out.println();
	}

}

