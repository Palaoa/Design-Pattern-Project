package FileManagement;

import java.io.Serializable;

public class MyDiskBlock implements Serializable{
	private static final long serialVersionUID = 1L;
	private static int size=5;    //磁盘块固定大小为10个字节
    private int id;               //记录磁盘块放置在磁盘上的位置
    private StringBuffer content=new StringBuffer();
    public MyDiskBlock(){
 	   
    }
    public MyDiskBlock(StringBuffer s){
 	   this.content=s;
    }
	public int getId() {
		return id;
	}
	public void setId(int id) {
		this.id = id;
	}
	public static int getSize() {
		return size;
	}
	
	public StringBuffer getContent() {
		return content;
	}
	public void setContent(StringBuffer content) {
		this.content = content;
	}
	
	public boolean canAdd(){
		if(content.length()>10) return false;
		else return true;
	}
}

