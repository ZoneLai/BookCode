<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%request.setCharacterEncoding("UTF-8"); %>
<!DOCTYPE HTML>
<html>
<head>
<meta charset="utf-8">
<title>根据是否登录显示不同的内容</title>
</head>
<body>
<c:choose>
	<c:when test="${empty param.username}">
	  <form name="form1" method="post" action="">
		用户名：
	      <input name="username" type="text" id="username"> 
	    <input type="submit" name="Submit" value="登录">
	  </form>
	</c:when>
	<c:otherwise>
		[${param.username }] 欢迎访问我公司网站！
	</c:otherwise>
</c:choose>
</body>
</html>
