<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%@ page import = "java.sql.*" %> 
    
<%
	Connection conn=null;
	String driver = "oracle.jdbc.driver.OracleDriver";
	String url = "jdbc:oracle:thin:@localhost:1521:ORCL";
	PreparedStatement stmt=null;
	Boolean connect = false;
	String query="insert into USERS values(?,?,?,?)";
	String userId=request.getParameter("id");
	String userPw=request.getParameter("pw");
	String userPhone=request.getParameter("phone");
	String userMail=request.getParameter("mail");
	
	try{
	    Class.forName(driver);
	    conn=DriverManager.getConnection(url,"hsh","1234"); //자신의 아이디와 비밀번호
	    connect = true;
	    stmt=conn.prepareStatement(query);
	    stmt.setString(1,userId);
	    stmt.setString(2,userPw);
	    stmt.setString(3,userPhone);
	    stmt.setString(4,userMail);
	    stmt.executeUpdate();
	    conn.close();
	}catch(Exception e){
	    connect = false;
	    e.printStackTrace();
	}
%>
