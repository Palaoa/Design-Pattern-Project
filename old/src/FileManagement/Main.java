package FileManagement;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Stack;

import FileManagement.AllUser;
import FileManagement.MyDir;
import FileManagement.MyDisk;
import FileManagement.MyDiskBlock;
import FileManagement.MyFile;

public class Main {
	public static void main(String[] args) throws IOException {
		System.out.println("欢迎光临Karen文件系统,请输入您的用户名");
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String username;
		while ((username = br.readLine().trim()).equals(""))
			System.out.println("用户名输入有误，请重新输入");
		MyDir nowdir = new MyDir(username);
		System.out.println( "您好"+ username
				+ ",欢迎光临！" +" 您可以创建新的目录和文件，如需帮助，输入help查看帮助指令");
		MyDir dirsave = null;
		MyFile filesave = null;
		while (true) {
			System.out.print(username+"/");
			Stack<String> brid=new Stack<String>();
			
			MyDir k = new MyDir();
			k = nowdir;
			while (nowdir.getFatherDir() != null) // 循环更新父目录磁盘块(添加)和大小，直至根目录
			{
				brid.push(nowdir.getName()+"/");
				nowdir = nowdir.getFatherDir();
			}
			nowdir = k;
			while(!brid.empty())
           System.out.print(brid.pop());
			
			String s = br.readLine().trim();

			

			if (s.equals("ls")) // --->目录显示,1
				nowdir.ls();
			else if (s.startsWith("cd") && !s.equals("cd ..")) { // --->跳转,1
				String real = s.substring(3, s.length());
				MyDir a = nowdir.cd(real);
				if (a != null) {
					MyDir b = nowdir;
					nowdir = a;
					nowdir.setFatherDir(b);
				} else
					System.out.println("您输入的目录名有误，请重新输入");

			} else if (s.equals("cd ..")) { // --->返回,1
				if (nowdir.cdReturn() != null)
					nowdir = nowdir.cdReturn();
				else
					System.out.println("已经退到根目录");

			} else if (s.startsWith("vim") && s.length() > 4) { // --->创建文件,1
				String real = s.substring(4, s.length());
				nowdir.addFile(new MyFile(real, 0, 0));

			} else if (s.startsWith("rmfile") && s.length() > 7) { // --->删除文件，1
				String real = s.substring(7, s.length());
				MyFile a = nowdir.getFile(real);
				if (a != null) {
					ArrayList<MyDiskBlock> blocklist = a.getBlocklist();
					ArrayList<Integer> thenw = new ArrayList<Integer>();
					for (MyDiskBlock one : blocklist) {
						MyDisk.getInstance().deleteUsed(one.getId());
						thenw.add(one.getId());
					}
					nowdir.deleteFile(real);

					MyDir save2 = new MyDir();
					save2 = nowdir;
					while (nowdir.getFatherDir() != null) // 循环更新父目录磁盘块（删除）和大小，直至根目录
					{

						nowdir.removeold(thenw);
						nowdir.updateSize();
						nowdir = nowdir.getFatherDir();
					}
					nowdir = save2;

					System.out.println("删除成功");
				} else
					System.out.println("对不起，该文件不存在");
			} else if (s.startsWith("rnmfile") && s.length() > 8) { // --->文件重命名
				String real = s.substring(8, s.length());
				MyFile a = nowdir.getFile(real);
				if (a != null) {
					System.out.println("请输入新的文件名");
					String newname = br.readLine().trim();
					if (nowdir.canPasteFile(new MyFile(newname))) { // 判断是否存在同名文件
						if (!newname.equals("")) {
							nowdir.deleteFile(real);
							MyFile thnew = a;
							thnew.setName(newname);
							nowdir.addFile(thnew);
							System.out.println("文件重命名成功!");
						}
					} else
						System.out.println("对不起，已经存在同名文件");

				} else
					System.out.println("对不起，该文件不存在");
			} else if (s.equals("open")) { // --->文件编辑,1
				System.out.println("请输入文件名称");
				String filename = br.readLine();
				MyFile a = nowdir.getFile(filename);
				if (a != null) {
					System.out.println("请编辑");
					ArrayList<MyDiskBlock> list = a.getBlocklist();
					ArrayList<Integer> oldused = new ArrayList<Integer>(); // 用来保存原本文件的磁块号

					StringBuffer all = new StringBuffer();
					for (MyDiskBlock one : list) {
						oldused.add(one.getId());
						all.append(one.getContent());
						MyDisk.getInstance().deleteUsed(one.getId());
					}

					MyDir save1 = new MyDir();
					save1 = nowdir;
					while (nowdir.getFatherDir() != null) // 循环更新父目录磁盘块，直至根目录
					{

						nowdir.removeold(oldused);
						nowdir.updateSize();
						nowdir = nowdir.getFatherDir();
					}
					nowdir = save1;

					System.out.println(all);
					StringBuffer realcontent = new StringBuffer(br.readLine());
					int point = 0;
					ArrayList<MyDiskBlock> newFileBlocklist = new ArrayList<MyDiskBlock>();

					ArrayList<Integer> thenw = new ArrayList<Integer>();
					int blocksize = MyDiskBlock.getSize();
					int sizecount = 0;
					if (realcontent.length() > blocksize) {
						for (int i = 0; i < realcontent.length() - blocksize; i = i
								+ blocksize) {
							StringBuffer op = new StringBuffer(
									realcontent.substring(i, i + blocksize));
							MyDiskBlock newblock = new MyDiskBlock(op);
							MyDisk.getInstance().addUsed(newblock);
							thenw.add(newblock.getId());
							newFileBlocklist.add(newblock);
							point = i;
							sizecount++;
						}
						StringBuffer rest = new StringBuffer(
								realcontent.substring(point + blocksize,
										realcontent.length()));
						sizecount++;
						MyDiskBlock ano = new MyDiskBlock(rest);
						MyDisk.getInstance().addUsed(ano); // 修改后的内容保存到磁盘
						thenw.add(ano.getId());
						newFileBlocklist.add(ano); // 保存到文件
					} else {
						StringBuffer shortone = new StringBuffer(
								realcontent.substring(0, realcontent.length()));
						MyDiskBlock one = new MyDiskBlock(shortone);
						sizecount++;
						MyDisk.getInstance().addUsed(one);
						thenw.add(one.getId());
						newFileBlocklist.add(one);
					}
					a.setOldsize(a.getNewsize()); // 将原本的文件大小置为上一次文件大小

					int newsize = sizecount * blocksize;
					a.setNewsize(newsize); // 设置文件的最新大小
					
					

					MyDir save2 = new MyDir();
					save2 = nowdir;
					while (nowdir.getFatherDir() != null) // 循环更新父目录磁盘块(添加)和大小，直至根目录
					{

						nowdir.addnew(thenw);
						nowdir.updateSize();
						nowdir = nowdir.getFatherDir();
					}
					nowdir = save2;

					a.setBlocklist(newFileBlocklist);
					System.out.println("编辑成功!");
				} else
					System.out.println("对不起，文件名输入有误");

			} else if (s.startsWith("vi") && s.length() > 3) { // 显示文件内容,1
				String filename = s.substring(3, s.length());
				MyFile a = nowdir.getFile(filename);
				if (a != null) {
					ArrayList<MyDiskBlock> list = a.getBlocklist();

					StringBuffer all = new StringBuffer();
					for (MyDiskBlock one : list) {
						all.append(one.getContent());
					}

					System.out.println(all);
				} else
					System.out.println("文件名称输入有误");

			} else if (s.startsWith("cpfile") && s.length() > 7) { // --->文件复制,1
				String real = s.substring(7, s.length());
				MyFile a = nowdir.getFile(real);
				if (a != null) {
					filesave=new MyFile();
					filesave = a;
					System.out.println("复制文件到剪贴板成功");
				} else
					System.out.println("对不起，文件名输入有误");
			} else if (s.equals("ptfile")) { // --->文件粘贴,1
				if (filesave != null) {
					ArrayList<MyDiskBlock> fileblocklist = filesave
							.getBlocklist();
					if (nowdir.canPasteFile(filesave)) { // 判断目录下是否有同名文件
						StringBuffer realcontent = new StringBuffer();
						for (MyDiskBlock one : fileblocklist) {
							realcontent.append(one.getContent()); // 先将文件中的StringBuffer全部拷贝出来
						}

						int point = 0;
						ArrayList<MyDiskBlock> newFileBlocklist = new ArrayList<MyDiskBlock>(); // 创建新的磁盘块列表用来存放这个StringBuffer
						int blocksize = MyDiskBlock.getSize();
						ArrayList<Integer> thenw = new ArrayList<Integer>();
						if (realcontent.length() > blocksize) {
							for (int i = 0; i < realcontent.length()
									- blocksize; i = i + blocksize) {
								StringBuffer op = new StringBuffer(
										realcontent.substring(i, i + blocksize));
								MyDiskBlock newblock = new MyDiskBlock(op);
								MyDisk.getInstance().addUsed(newblock); //
								thenw.add(newblock.getId());
								newFileBlocklist.add(newblock);
								point = i;
							}
							StringBuffer rest = new StringBuffer(
									realcontent.substring(point + blocksize,
											realcontent.length()));
							MyDiskBlock ano = new MyDiskBlock(rest);
							MyDisk.getInstance().addUsed(ano); // 修改后的内容保存到磁盘,一定要先保存到磁盘,在分配好磁盘号之后,再保存到文件
							thenw.add(ano.getId());
							newFileBlocklist.add(ano); // 保存到文件
						} else {
							StringBuffer shortone = new StringBuffer(
									realcontent.substring(0,
											realcontent.length()));
							MyDiskBlock one = new MyDiskBlock(shortone);
							MyDisk.getInstance().addUsed(one);
							thenw.add(one.getId());
							newFileBlocklist.add(one);
						}

						MyDir save2 = new MyDir();
						save2 = nowdir;
						while (nowdir.getFatherDir() != null) // 循环更新父目录磁盘块(添加)和大小，直至根目录
						{

							nowdir.addnew(thenw);
							nowdir.updateSize();
							nowdir = nowdir.getFatherDir();
						}
						nowdir = save2;

						MyFile anoth = new MyFile(filesave.getName()); // 新建一个文件用来保存复制板里的信息,不要直接用filesave,之前在此处出错,debug用时2小时,就是因为没new一个新的MyFile
						anoth.setBlocklist(newFileBlocklist);
						anoth.setNewsize(filesave.getNewsize());
						anoth.setOldsize(filesave.getOldsize());

						nowdir.addFile(anoth);
					} else
						System.out.println("该目录下已经有同名文件，不能粘贴");
				}

				else
					System.out.println("剪贴板中没有文件");
			}

			else if (s.startsWith("rnmdir") && s.length() > 7) { // --->目录重命名,1
				String real = s.substring(7, s.length());
				MyDir old = nowdir.getDir(real);
				if (old != null) {
					System.out.println("请输入新的目录名");
					String newname = br.readLine().trim();
					if (nowdir.canPasteDir(new MyDir(newname))) { // 确认该目录下无同名目录
						if (newname != "") {
							nowdir.deleteDir(real);
							MyDir thnew = old;
							thnew.setName(newname);
							nowdir.addDir(thnew);
							System.out.println("目录重命名成功!");
						} else {
							System.out.println("文件名未输入");
						}
					} else
						System.out.println("已经存在同名目录");

				} else
					System.out.println("对不起，不存在该目录");

			} else if (s.startsWith("rmdir") && s.length() > 6) { // 删除目录，1
				String real = s.substring(6, s.length());
				MyDir old = nowdir.getDir(real);
				if (old != null) {
					ArrayList<Integer> all = new ArrayList<Integer>();
					all = old.getUsedblock();
					for (Integer a : all) {
						MyDisk.getInstance().deleteUsed(a);
					}

					nowdir.deleteDir(real);

					MyDir save2 = new MyDir();
					save2 = nowdir;
					while (nowdir.getFatherDir() != null) // 循环更新父目录磁盘块(删除)和大小，直至根目录
					{

						nowdir.removeold(all);
						nowdir.updateSize();
						nowdir = nowdir.getFatherDir();
					}
					nowdir = save2;
				} else
					System.out.println("对不起，不存在该目录");
			}

			else if (s.startsWith("mkdir") && s.length() > 6) { // 创建目录，1
				String dirname = s.substring(6, s.length());
				MyDir dir = new MyDir(dirname, 0, 0);
				nowdir.addDir(dir);

			} else if (s.startsWith("cpdir") && s.length() > 6) { // 复制目录
				String real = s.substring(6, s.length());
				MyDir a = nowdir.getDir(real);
				if (a != null) {
					dirsave=new MyDir();
					dirsave = (MyDir) MyDir.cloneObject(a);
					System.out.println("目录成功复制到剪切板");
				} else
					System.out.println("对不起，不存在该目录");
			} else if (s.equals("ptdir")) { // 粘贴目录
				if (dirsave != null) {
					// MyDir ins=new MyDir();
					MyDir instance = new MyDir();
					instance = (MyDir) MyDir.cloneObject(dirsave);
					if (nowdir.canPasteDir(instance)) { // 检查无同名目录，才能添加；
						instance.setFatherDir(nowdir);
						ArrayList<Integer> oldused = instance.getUsedblock();

						ArrayList<Integer> thenew = new ArrayList<Integer>();
						new ArrayList<MyDiskBlock>();
						for (int i = 0; i < oldused.size(); i++) {
							MyDiskBlock a = new MyDiskBlock();
							MyDisk.getInstance().addUsed(a);
							thenew.add(a.getId());

						}
						instance.setUsedblock(thenew);
						nowdir.addDir(instance);

						MyDir save2 = new MyDir();
						save2 = nowdir;
						while (nowdir.getFatherDir() != null) // 循环更新父目录磁盘块(添加)和大小，直至根目录
						{

							nowdir.addnew(thenew);
							nowdir.updateSize();
							nowdir = nowdir.getFatherDir();
						}
						nowdir = save2;
					} else
						System.out.println("目录下已经有同名目录，无法粘贴");

				} else
					System.out.println("剪切板中没有目录");
			} else if (s.equals("showdisk")) { // 显示磁盘使用情况，1
				MyDisk.getInstance().showUsed();
			} else if (s.equals("help")) { // 显示帮助，1
				System.out
						.println("----------------------------------1.显示和跳转操作------------------------------------");
				System.out
						.println("ls   :显示文件目录                    cd [dirname]:跳转到指定目录                     cd ..跳转到上层目录        \n");
				System.out
						.println("----------------------------------2.目录操作------------------------------------------");
				System.out
						.println("mkdir [dirname]:创建目录                   ptdir [dirname]:粘贴目录                  cpdir [dirname]:拷贝目录 ");
				System.out
						.println("rnmdir [dirname]:重命名目录           rmdir [dirname]:删除目录\n");
				System.out
						.println("----------------------------------3.文件操作------------------------------------------");
				System.out
						.println("vim [filename]:创建文件                 ptfile [filename]:粘贴文件        rnmfile [filename]:重命名文件 ");
				System.out
						.println("cpfile [filename]:拷贝文件         rmfile [filename]:删除文件        vi [filename]:显示文件内容");
				System.out.println("open   :打开文件");
				System.out.println("(open文件后，输入正确的文件名就能打开指定文件进行编辑了)\n");
				System.out
						.println("----------------------------------4.磁盘操作------------------------------------------");
				System.out.println("showdisk  :显示磁盘使用情况\n");
				System.out
						.println("----------------------------------5.注销登录或退出系统---------------------------------");
				System.out.println("logout  :注销登录                            exit  :退出系统\n");
				System.out
						.println("--------------------------------------------------------------------------------------");
			} else if (s.equals("exit")) {
				System.out.println("您已经退出系统");
				System.exit(0);
			} else if (s.equals("cls")) {
				for (int i = 0; i <= 30; i++) {
					System.out.println();
				}
			} else if (s.equals("ls?"))
				System.out.println("输入ls,用以显示当前目录下所有的目录文件");
			else if (s.equals("cd?"))
				System.out.println("输入 cd [dirname]:   跳转到指定目录");
			else if (s.equals("cd ..?"))
				System.out.println("输入cd ..跳转到上层目录 ");
			else if (s.equals("mkdir?"))
				System.out.println("输入mkdir [dirname]:创建目录 ");
			else if (s.equals("cpdir?"))
				System.out.println("输入cpdir [dirname]:拷贝目录 ");
			else if (s.equals("ptdir?"))
				System.out.println("输入 ptdir [dirname]:粘贴目录 ");
			else if (s.equals("rnmdir?"))
				System.out.println("输入rnmdir [dirname]:重命名目录 ");
			else if (s.equals("rmdir?"))
				System.out.println("输入 rmdir [dirname]:删除目录 ");

			else if (s.equals("ptfile?"))
				System.out.println("输入ptfile [filename]:粘贴文件");
			else if (s.equals("cpfile?"))
				System.out.println("输入 cpfile [filename]:拷贝文件  ");
			else if (s.equals("rnmfile?"))
				System.out.println("输入rnmfile [filename]:重命名文件 ");
			else if (s.equals("rmfile?"))
				System.out.println("输入 rmfile [filename]:删除文件");
			else if (s.equals("open?"))
				System.out.println("输入open 打开文件     之后输入正确的文件名就能打开进行编辑了");
			else if (s.equals("showdisk?"))
				System.out.println("输入showdisk  :显示磁盘使用情况 ");
			else if (s.equals("exit?"))
				System.out.println("输入exit  :退出该系统 ");
			else if(s.equals("logout")){
				MyDir thisone = new MyDir();
				thisone = nowdir;
				while (nowdir.getFatherDir() != null) // 循环更新父目录磁盘块(添加)和大小，直至根目录
				{

					brid.push(nowdir.getName()+"/");
					nowdir = nowdir.getFatherDir();
				}
               AllUser.getInstance().addUser(thisone);
               System.out.println("您已经注销，您可以进行以下选择：①输入exit离开文件系统    ②输入login+已经存在的其他用户名 进行登陆  ③输入add+新的用户名  添加其他用户并登录");
               String in=br.readLine().trim();
               if(in.equals("exit"))  System.exit(0);
               else if (in.startsWith("login") && in.length() > 6) { //登陆原有的账号
   				String anouser = in.substring(6, in.length());
   				if(AllUser.getInstance().whetherExist(anouser)){
   					nowdir=AllUser.getInstance().getUserDir(anouser);
   	   				System.out.println("欢迎光临" + anouser
   	  						+ "   您可以创建新的目录和文件，如需帮助，输入help查看帮助指令");
   	   				username=anouser;
   				}else System.out.println("不存在该用户");
   					
               }
               else if (in.startsWith("add") && in.length() > 4) { //创建新账号并登录
      				String newuser = in.substring(4, in.length());
      				if(!AllUser.getInstance().whetherExist(newuser)){
      					nowdir= new MyDir(newuser);
          				System.out.println("欢迎光临" + newuser
          						+ "   您可以创建新的目录和文件，如需帮助，输入help查看帮助指令");
          					AllUser.getInstance().addUser(nowdir);
          					username=newuser;
      				}
      				else System.out.println("已经存在同名用户");
      					
                  }
               else {
            	   System.out.println("无该指令，请重新输入");
               }
            	   
			}
			else
				System.out.println("无该指令，请重新输入");
			
		}

	}

}

