<%@ page language="java" contentType="text/html; charset=gb2312"%>
<%@ page import="com.javabean.Image" %>
<% Image logon=(Image)request.getAttribute("logonimg"); %>
<html>
<head>
<title>�û���¼</title>
<link rel="stylesheet" type="text/css" href="css/style.css">
</head>
<body>
 <center>
   <table border="1"  style="margin-top:150" width="250" height="90">
     <tr height="20" bgcolor="lightgrey"><td align="center">��ӭ��¼��</td>
     <tr>
        <td align="center">
          �������ˡ��û���¼��ͼƬ��<br>
          ��굥��ʱ��λ��Ϊ&nbsp;&nbsp;
          X��<%=logon.getX() %>&nbsp;
          Y��<%=logon.getY() %>
        </td>
     </tr>
   </table>
   <a href="index.jsp">����</a>
 </center>
</body>
</html>