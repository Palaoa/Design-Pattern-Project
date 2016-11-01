package FileManagement;

import java.io.Serializable;
import java.util.ArrayList;

public class MyFile implements Serializable{

	private static final long serialVersionUID = 1L;
	private int oldsize; // �޸�ǰ�ļ���С
	private int newsize; // �޸ĺ��ļ���С

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

	private String name; // �����ļ�����

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
	 * һ���ļ��ϴ���Ӵ��̿��Ա�����ļ�����
	 * 
	 * @param a
	 *            Ҫ��ӵ��ļ������б�Ĵ��̿��
	 */
	public void addBlock(MyDiskBlock a) {
		this.blocklist.add(a);
	}
}
