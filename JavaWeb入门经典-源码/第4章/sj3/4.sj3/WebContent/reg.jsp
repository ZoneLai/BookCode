<%@ page language="java" contentType="text/html; charset=gb2312"%>
<%@ page import="com.javabean.Image" %>
<% Image reg=(Image)request.getAttribute("regimg"); %>
<html>
<head>
<title>�û�ע��</title>
<link rel="stylesheet" type="text/css" href="css/style.css">
</head>
<body>
 <center>
   <table border="1"  style="margin-top:150" width="250" height="90">
     <tr height="20" bgcolor="lightgrey"><td align="center">��ӭע�ᣡ</td>
     <tr>
        <td align="center">
          �������ˡ��û�ע�ᡱͼƬ��<br>
          ��굥��ʱ��λ��Ϊ&nbsp;&nbsp;
          X��<%=reg.getX() %>
          Y��<%=reg.getY() %>
        </td>
     </tr>
   </table>
   <a href="index.jsp">����</a>
 </center>
</body>
</html>