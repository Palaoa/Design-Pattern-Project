package FileManagement;

import java.io.Serializable;
import java.util.ArrayList;

public class MyFile implements Serializable{

	private static final long serialVersionUID = 1L;
	private int oldsize; // 修改前文件大小
	private int newsize; // 修改后文件大小

	public int getOldsize() {
		return oldsize;
	}

	public void setOldsize(int oldsize) {
		this.oldsize = oldsize;
	}

	public int getNewsize() {
		return newsize;
	}

	public void setNewsize(int newsize) {
		this.newsize = newsize;
	}

	private String name; // 保存文件名字

	public MyFile() {

	}

	public MyFile(String name) {
		this.name = name;
	}

	public MyFile(String name, int old, int tnew) {
		this(name);
		this.oldsize = old;
		this.newsize = tnew;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	private ArrayList<MyDiskBlock> blocklist = new ArrayList<MyDiskBlock>();

	public ArrayList<MyDiskBlock> getBlocklist() {
		return blocklist;
	}

	public void setBlocklist(ArrayList<MyDiskBlock> blocklist) {
		this.blocklist = blocklist;
	}

	public void clearBlocklist() {
		this.blocklist.clear();
	}

	/**
	 * 一个文件较大，添加磁盘块以保存该文件内容
	 * 
	 * @param a
	 *            要添加到文件磁盘列表的磁盘块号
	 */
	public void addBlock(MyDiskBlock a) {
		this.blocklist.add(a);
	}
}
