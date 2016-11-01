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
	//Ŀ¼��
	private String name;
	//��Ŀ¼ 
	private MyDir fatherDir;
	//��Ŀ¼��Ŀ¼�б� 
	private Hashtable<String, MyDir> dirlist = new Hashtable<String, MyDir>();
	//��Ŀ¼���ļ��б� 
	private Hashtable<String, MyFile> filelist = new Hashtable<String, MyFile>();
	//��Ŀ¼��С
	private int oldsize;
	private int newsize;
	/** ��¼��Ŀ¼��ռ�õĴ��̿���� */
	private ArrayList<Integer> usedblock = new ArrayList<Integer>();

	//��¼��Ŀ¼��ռ�õ��µĴ��̿����
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
	    	 System.out.println("Ŀ¼����ʱ�������������¿���");
		}
		 return objx;
		
	}
	 
	 //�ж��ܷ�ճ����Ŀ¼
    public boolean canPasteDir(MyDir a){
    	return !dirlist.containsKey(a.getName());
    }
    
    // �ж��ܷ�ճ�����ļ�
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
	
	//��Ŀ¼�����Ӵ��̿��
	public void addnew(ArrayList<Integer> all){
		for(Integer a:all){
			usedblock.add(a);
		}
	}
	
	//����Ŀ¼�Ĵ�С
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

	//��ʾĿ¼�������ļ���Ŀ¼
	public void ls() {
		int count = 0;
		Iterator<String> a = filelist.keySet().iterator();
		while (a.hasNext()) {
			MyFile inst = filelist.get(a.next());
			System.out.print(inst.getName() + "(�ļ�)---��С:" + inst.getNewsize()
					+ "     ");
			count++;
		}
		Iterator<String> b = dirlist.keySet().iterator();
		while (b.hasNext()) {
			MyDir inst = dirlist.get(b.next());
			System.out.print(inst.getName() + "(Ŀ¼)---��С:" + inst.getNewsize()
					+ "     ");
			count++;
		}
		if (count == 0)
			System.out.println("�Բ��𣬵�ǰĿ¼�²����ļ�");
		else
			System.out.println();
	}

	//��תcd
	public MyDir cd(String name) {

		return dirlist.get(name);
	}

	public MyDir cdReturn() {
		return fatherDir;
	}

	//����Ŀ¼����ø�Ŀ¼
	public MyDir getDir(String oldname) {
		return dirlist.get(oldname);
	}

	//���Ŀ¼
	public void addDir(MyDir a) {
		if(dirlist.containsKey(a.getName()))
		     System.out.println("�Ѿ�����ͬ��Ŀ¼������ʧ��");
		else dirlist.put(a.getName(), a);
	}

	// ɾ��Ŀ¼
	public void deleteDir(String dirname) {
		dirlist.remove(dirname);
	}

	//�����ļ�����ø��ļ�
	public MyFile getFile(String filename) {
		return filelist.get(filename);
	}

	//Ŀ¼�����һ���ļ�
	public void addFile(MyFile a) {
		if(filelist.containsKey(a.getName()))
				System.out.println("�Բ��𣬸�Ŀ¼���Ѿ�����ͬ���ļ�������ʧ��");
		else filelist.put(a.getName(), a);
	}

	// ɾ���ļ�
	public void deleteFile(String filename) {
		filelist.remove(filename);
	}

}


