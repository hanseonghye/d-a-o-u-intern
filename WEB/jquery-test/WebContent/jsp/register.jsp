<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%@ page import = "java.sql.*" %> 

<%
	Connection conn=null;
	String driver = "oracle.jdbc.driver.OracleDriver";
	String url = "jdbc:oracle:thin:@localhost:1521:ORCL";
		
	Boolean connect = false;
		
	try{
	    Class.forName(driver);
	    conn=DriverManager.getConnection(url,"hsh","1234"); //자신의 아이디와 비밀번호
	    connect = true;
	    conn.close();
	}catch(Exception e){
	    connect = false;
	    e.printStackTrace();
	}
%>


<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<script src="/js/jquery-1.10.2.min.js"></script>
<style>
	label{
		width:120px;
  		display: inline-block;
	}
</style>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>Insert title here</title>
</head>
<body>
	<label for="id">등록 ID :</label> <input type="text" id="id" name="id" value="<%=request.getParameter("id") %>" readonly="readonly">
	<br>
	<label for="pw">비밀번호 :</label> <input type="password" id="pw" name="pw" value="<%=request.getParameter("pw") %>" readonly="readonly">
	<br>
	<label for="phone">핸드폰 번호 :</label> <input type="text" id="phone" name="phone" value="<%=request.getParameter("phone") %>" readonly="readonly">
	<br>
	<label for="mail">이메일 주소 :</label> <input type="text" id="mail" name="mail" value="<%=request.getParameter("mail") %>" readonly="readonly">
	<button id="ok">확인</button>
	
	<script>
		$(document).ready(function(){
			$("#ok").click( function(){
				console.log("ok click")
				$.ajax({
					url:'/jsp/insertDb.jsp',
					data:{
						id:$('#id').val(),
						pw:$('#pw').val(),
						phone:$('#phone').val(),
						mail:$('#mail').val()
					},
					type:'POST',
					datatype:'json',
					success:function(res){
						
					}
					
				})
				
			})
		})
	</script>

</body>
</html>