<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<jsp:useBean id="produce" class="com.wgh.Produce"></jsp:useBean>
<!DOCTYPE HTML>
<html>
<head>
<meta charset="utf-8">
<title>显示商品信息</title>
</head>
<body>
<div>
	<ul>
		<li>
			商品名称：<jsp:getProperty property="name" name="produce"/>
		</li>
		<li>
			价格：<jsp:getProperty property="price" name="produce"/>（元）
		</li>
		<li>
			数量：<jsp:getProperty property="count" name="produce"/>
		</li>
		<li>
			厂址：<jsp:getProperty property="factoryAdd" name="produce"/>
		</li>
	</ul>
</div>

</body>
</html>