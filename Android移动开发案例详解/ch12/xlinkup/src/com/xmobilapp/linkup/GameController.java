package com.xmobilapp.linkup;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;

import android.graphics.Point;
import android.os.Handler;
import android.os.Message;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.xmobilapp.linkup.GameView.OnItemClickListener;

public class GameController {

	// ����
	private static final int countX = 10;
	// ����
	private static final int countY = 12;
	// ͼƬ��С
	private static final int iconSize = 35;

	private Main app;

	private GameView gameView;
	// ��Ϸ����
	private int[][] map;

	private List<Point> path = new ArrayList<Point>();

	private RefreshHandler redrawHandler = new RefreshHandler();

	class RefreshHandler extends Handler {

		public static final int UPDATE_TXT = 0;

		public static final int UPDATE_IMAGE = 1;

		@Override
		public void handleMessage(Message msg) {
			switch (msg.what) {
			// �����ı���ʾ
			case UPDATE_TXT:
				TextView t = (TextView) app.findViewById(R.id.timing);
				t.setText("ʣ��ʱ�䣺" + remainTime + "�� ������" + help + "��");
				if (remainTime <= 0) {
					timer.cancel();
					app.setState(Main.STATE_LOSE);
				}
				break;
			// ������ͼ
			case UPDATE_IMAGE:
				gameView.invalidate();
				if (win()) {
					timer.cancel();
					app.setState(Main.STATE_WIN);
				} else if (die()) {
					shuffle();
				}
				break;
			}
		}

		// ��ʱˢ����ͼ
		public void sleep(long delayMillis) {
			this.removeMessages(0);
			Message msg = new Message();
			msg.what = UPDATE_IMAGE;
			sendMessageDelayed(msg, delayMillis);
		}
	};

	private OnItemClickListener itemClickListener = new OnItemClickListener() {

		public void onClick(Point position) {
			List<Point> selected = gameView.getSelected();
			// �����ѡ��һ�����ж��Ƿ������������ѡ�е�ǰ���ͼƬ
			if (selected.size() == 1) {
				if (link(selected.get(0), position)) {
					selected.add(position);
					gameView.drawLine(path.toArray(new Point[] {})); // ����
					redrawHandler.sleep(500); // 500ms�������ͼ���������ߺ�ͼƬ
				} else {
					// �������������ѡ��ͼƬ
					selected.clear();
					selected.add(position);
					gameView.invalidate();
				}
			} else {
				selected.add(position);
				gameView.invalidate();
			}
		}

	};
	// ��ʱ��
	private static final long totalTime = 200;
	// ʣ��ʱ��
	private long remainTime;
	// ��ʼʱ��
	private long startTime;
	// ��ʱ��
	private Timer timer;
	// ���ð�������
	private int help;

	class GameTimerTask extends TimerTask {

		@Override
		public void run() {
			// ����ʣ��ʱ��
			remainTime = totalTime
					- ((System.currentTimeMillis() - startTime) / 1000);
			Message msg = new Message();
			msg.what = RefreshHandler.UPDATE_TXT;
			redrawHandler.sendMessage(msg);
		}

	};

	// ��ʼ��Ϸ����ʼ������Ͳ���
	public void startGame(Main m) {
		generateMap();
		help = 5;
		remainTime = totalTime;
		resume(m);
	}

	public void pause() {
		timer.cancel();
	}

	public void resume(Main m) {
		app = m;
		gameView = new GameView(app);
		LinearLayout gameViewParent = (LinearLayout) app.findViewById(R.id.GameView);
		gameView.setIconWidth(iconSize);
		gameView.setIconHeight(iconSize);
		gameView.setIcons(Main.icons);
		gameView.setOnItemClickListener(itemClickListener);
		gameView.setMap(map);
		gameViewParent.addView(gameView, ViewGroup.LayoutParams.FILL_PARENT,
				ViewGroup.LayoutParams.FILL_PARENT);
		startTime = System.currentTimeMillis() - (totalTime - remainTime)
				* 1000;
		timer = new Timer();
		timer.schedule(new GameTimerTask(), 0, 100);
	}

	// ���ɳ�ʼ������
	private void generateMap() {
		int x = 1;
		int y = 0;
		map = new int[countX][countY];
		for (int i = 1; i < countX - 1; i++) {
			for (int j = 1; j < countY - 1; j++) {
				map[i][j] = x;
				if (y == 1) {
					x++;
					y = 0;
					if (x == Main.iconsCount + 1) {
						x = 1;
					}
				} else {
					y = 1;
				}
			}
		}
		shuffle();
	}

	// �������
	private void shuffle() {
		Random random = new Random();
		int tmpV, tmpX, tmpY;
		for (int y = 1; y < countY - 1; y++) {
			for (int x = 1; x < countX - 1; x++) {
				tmpV = map[x][y];
				tmpX = random.nextInt(countX - 2) + 1;
				tmpY = random.nextInt(countY - 2) + 1;
				map[x][y] = map[tmpX][tmpY];
				map[tmpX][tmpY] = tmpV;
			}
		}
		if (die()) {
			shuffle();
		}
	}

	List<Point> p1E = new ArrayList<Point>();
	List<Point> p2E = new ArrayList<Point>();

	private boolean link(Point p1, Point p2) {
		if (p1.equals(p2)) {
			return false;
		}
		path.clear();
		if (map[p1.x][p1.y] == map[p2.x][p2.y]) {
			// ֱ��
			if (linkD(p1, p2)) {
				path.add(p1);
				path.add(p2);
				return true;
			}
			// һ��
			Point p = new Point(p1.x, p2.y);
			if (map[p.x][p.y] == 0) {
				if (linkD(p1, p) && linkD(p, p2)) {
					path.add(p1);
					path.add(p);
					path.add(p2);
					return true;
				}
			}
			p = new Point(p2.x, p1.y);
			if (map[p.x][p.y] == 0) {
				if (linkD(p1, p) && linkD(p, p2)) {
					path.add(p1);
					path.add(p);
					path.add(p2);
					return true;
				}
			}
			// ����
			// ��������
			expandH(p1, p1E);
			expandH(p2, p2E);
			// �ж��Ƿ����
			for (Point pt1 : p1E) {
				for (Point pt2 : p2E) {
					if (pt1.x == pt2.x) {
						if (linkD(pt1, pt2)) {
							path.add(p1);
							path.add(pt1);
							path.add(pt2);
							path.add(p2);
							return true;
						}
					}
				}
			}
			// ��������
			expandV(p1, p1E);
			expandV(p2, p2E);
			// �ж��Ƿ����
			for (Point pt1 : p1E) {
				for (Point pt2 : p2E) {
					if (pt1.y == pt2.y) {
						if (linkD(pt1, pt2)) {
							path.add(p1);
							path.add(pt1);
							path.add(pt2);
							path.add(p2);
							return true;
						}
					}
				}
			}
			return false;
		}
		return false;
	}

	// �ж��Ƿ���ֱ��
	private boolean linkD(Point p1, Point p2) {
		if (p1.x == p2.x) {
			int y1 = Math.min(p1.y, p2.y);
			int y2 = Math.max(p1.y, p2.y);
			boolean flag = true;
			for (int y = y1 + 1; y < y2; y++) {
				if (map[p1.x][y] != 0) {
					flag = false;
					break;
				}
			}
			if (flag) {
				return true;
			}
		}
		if (p1.y == p2.y) {
			int x1 = Math.min(p1.x, p2.x);
			int x2 = Math.max(p1.x, p2.x);
			boolean flag = true;
			for (int x = x1 + 1; x < x2; x++) {
				if (map[x][p1.y] != 0) {
					flag = false;
					break;
				}
			}
			if (flag) {
				return true;
			}
		}
		return false;
	}

	// ����Ѱ�ҿɴ�ĵ�
	private void expandH(Point p, List<Point> l) {
		l.clear();
		for (int x = p.x + 1; x < countX; x++) {
			if (map[x][p.y] != 0) {
				break;
			}
			l.add(new Point(x, p.y));
		}
		for (int x = p.x - 1; x >= 0; x--) {
			if (map[x][p.y] != 0) {
				break;
			}
			l.add(new Point(x, p.y));
		}
	}

	// ����Ѱ�ҿɴ�ĵ�
	private void expandV(Point p, List<Point> l) {
		l.clear();
		for (int y = p.y + 1; y < countY; y++) {
			if (map[p.x][y] != 0) {
				break;
			}
			l.add(new Point(p.x, y));
		}
		for (int y = p.y - 1; y >= 0; y--) {
			if (map[p.x][y] != 0) {
				break;
			}
			l.add(new Point(p.x, y));
		}
	}

	// �ж��Ƿ��п����ĵ�
	private boolean die() {
		for (int y = 1; y < countY - 1; y++) {
			for (int x = 1; x < countX - 1; x++) {
				if (map[x][y] != 0) {
					for (int j = y; j < countY - 1; j++) {
						if (j == y) {
							for (int i = x + 1; i < countX - 1; i++) {
								if (map[i][j] == map[x][y]
										&& link(new Point(x, y),
												new Point(i, j))) {
									return false;
								}
							}
						} else {
							for (int i = 1; i < countX - 1; i++) {
								if (map[i][j] == map[x][y]
										&& link(new Point(x, y),
												new Point(i, j))) {
									return false;
								}
							}
						}
					}
				}
			}
		}
		return true;
	}

	// �ж��Ƿ�����ȫ����
	private boolean win() {
		for (int x = 0; x < countX; x++) {
			for (int y = 0; y < countY; y++) {
				if (map[x][y] != 0)
					return false;
			}
		}
		return true;
	}

	// �����ʱ�Զ�����
	public void autoErase() {
		if (help == 0)
			return;
		help--;
		die();
		List<Point> l = gameView.getSelected();
		l.clear();
		l.add(path.get(0));
		l.add(path.get(path.size() - 1));
		gameView.drawLine(path.toArray(new Point[] {}));
		redrawHandler.sleep(500);
	}
}
