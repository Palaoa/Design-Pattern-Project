package FileManagement;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Iterator;
//import java.util.Map.Entry;


public class MyDir implements Serializable{

	private static final long serialVersionUID = 1L;
	//目录名
	private String name;
	//父目录 
	private MyDir fatherDir;
	//该目录下目录列表 
	private Hashtable<String, MyDir> dirlist = new Hashtable<String, MyDir>();
	//该目录下文件列表 
	private Hashtable<String, MyFile> filelist = new Hashtable<String, MyFile>();
	//该目录大小
	private int oldsize;
	private int newsize;
	/** 记录该目录所占用的磁盘块序号 */
	private ArrayList<Integer> usedblock = new ArrayList<Integer>();

	//记录该目录所占用的新的磁盘块序号
	// private ArrayList<Integer> newusedblock=new ArrayList<Integer>();

	public ArrayList<Integer> getUsedblock() {
		return usedblock;
	}
	   
	 public static Object cloneObject(Object obj){
	     Object objx=null;
		 try{
	    	 ByteArrayOutputStream  byteOut = new ByteArrayOutputStream();  
		        ObjectOutputStream out = new ObjectOutputStream(byteOut);  
		        out.writeObject(obj);         
		        ByteArrayInputStream byteIn = new ByteArrayInputStream(byteOut.toByteArray());  
		        ObjectInputStream in =new ObjectInputStream(byteIn);  
		        objx=in.readObject();
		        
	     }catch (Exception e) {
			// TODO: handle exception
	    	 System.out.println("目录拷贝时发生错误，请重新拷贝");
		}
		 return objx;
		
	}
	 
	 //判断能否粘贴该目录
    public boolean canPasteDir(MyDir a){
    	return !dirlist.containsKey(a.getName());
    }
    
    // 判断能否粘贴该文件
    public boolean canPasteFile(MyFile a){
    	return !filelist.containsKey(a.getName());
    }
    
    
	public void setUsedblock(ArrayList<Integer> usedblock) {
		this.usedblock = usedblock;
	}
	
	public void removeold(ArrayList<Integer> all){
		for(Integer a:all){
			if (usedblock.contains(a))
			usedblock.remove(a);
		}
	}
	
	//在目录下增加磁盘块号
	public void addnew(ArrayList<Integer> all){
		for(Integer a:all){
			usedblock.add(a);
		}
	}
	
	//更新目录的大小
	public void updateSize(){
		this.newsize=MyDiskBlock.getSize()*usedblock.size();
	}

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

	public MyDir() {

	}

	public MyDir(String name) {
		this.name = name;
	}

	public MyDir(String name, int old, int tnew) {
		this(name);
		this.newsize = tnew;
		this.oldsize = old;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public MyDir getFatherDir() {
		return fatherDir;
	}

	public void setFatherDir(MyDir fatherDir) {
		this.fatherDir = fatherDir;

	}

	//显示目录下所有文件和目录
	public void ls() {
		int count = 0;
		Iterator<String> a = filelist.keySet().iterator();
		while (a.hasNext()) {
			MyFile inst = filelist.get(a.next());
			System.out.print(inst.getName() + "(文件)---大小:" + inst.getNewsize()
					+ "     ");
			count++;
		}
		Iterator<String> b = dirlist.keySet().iterator();
		while (b.hasNext()) {
			MyDir inst = dirlist.get(b.next());
			System.out.print(inst.getName() + "(目录)---大小:" + inst.getNewsize()
					+ "     ");
			count++;
		}
		if (count == 0)
			System.out.println("对不起，当前目录下并无文件");
		else
			System.out.println();
	}

	//跳转cd
	public MyDir cd(String name) {

		return dirlist.get(name);
	}

	public MyDir cdReturn() {
		return fatherDir;
	}

	//根据目录名获得该目录
	public MyDir getDir(String oldname) {
		return dirlist.get(oldname);
	}

	//添加目录
	public void addDir(MyDir a) {
		if(dirlist.containsKey(a.getName()))
		     System.out.println("已经存在同名目录，操作失败");
		else dirlist.put(a.getName(), a);
	}

	// 删除目录
	public void deleteDir(String dirname) {
		dirlist.remove(dirname);
	}

	//根据文件名获得该文件
	public MyFile getFile(String filename) {
		return filelist.get(filename);
	}

	//目录下添加一个文件
	public void addFile(MyFile a) {
		if(filelist.containsKey(a.getName()))
				System.out.println("对不起，该目录下已经存在同名文件，操作失败");
		else filelist.put(a.getName(), a);
	}

	// 删除文件
	public void deleteFile(String filename) {
		filelist.remove(filename);
	}

}


