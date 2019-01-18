<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
    
<%
	String inputId=request.getParameter("id");
	String inputPw=request.getParameter("pw");
	
	if(inputId.equals("abcd") && inputPw.equals("1234") )
		out.print("success");
	else
		out.print("false");
%>
