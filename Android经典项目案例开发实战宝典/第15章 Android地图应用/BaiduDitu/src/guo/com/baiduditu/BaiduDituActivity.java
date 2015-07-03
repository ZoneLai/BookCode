package guo.com.baiduditu;

import com.baidu.mapapi.BMapManager;
import com.baidu.mapapi.GeoPoint;
import com.baidu.mapapi.MKAddrInfo;
import com.baidu.mapapi.MKBusLineResult;
import com.baidu.mapapi.MKDrivingRouteResult;
import com.baidu.mapapi.MKPoiInfo;
import com.baidu.mapapi.MKPoiResult;
import com.baidu.mapapi.MKSearch;
import com.baidu.mapapi.MKSearchListener;
import com.baidu.mapapi.MKSuggestionResult;
import com.baidu.mapapi.MKTransitRouteResult;
import com.baidu.mapapi.MKWalkingRouteResult;
import com.baidu.mapapi.MapActivity;
import com.baidu.mapapi.MapController;
import com.baidu.mapapi.MapView;
import com.baidu.mapapi.RouteOverlay;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
//��ͼ������
public class BaiduDituActivity extends MapActivity {
	//������ť
	Button mBtnSearch = null;	
	//��ͼView
	MapView mMapView = null;	
	//����ģ�飬Ҳ��ȥ����ͼģ�����ʹ��
	MKSearch mSearch = null;	
	//��������
	String  mCityName = null;
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
        setContentView(R.layout.busline);
        //ȡ��Ӧ�ó���ʵ��
		BMapApp app = (BMapApp)this.getApplication();
		if (app.mBMapMan == null) {
			//ʵ������ͼ������
			app.mBMapMan = new BMapManager(getApplication());
			//��ʼ����ͼ������
			app.mBMapMan.init(app.mStrKey, new BMapApp.MyGeneralListener());
		}
		app.mBMapMan.start();
        //��ʼ����ͼActivity
        super.initMapActivity(app.mBMapMan);
        //��õ�ͼ����Ԫ��
        mMapView = (MapView)findViewById(R.id.bmapView);
        //���÷Ŵ���С������
        mMapView.setBuiltInZoomControls(true);
        //���������Ŷ���������Ҳ��ʾoverlay,Ĭ��Ϊ������
        mMapView.setDrawOverlayWhenZooming(true);   
        // �õ�mMapView�Ŀ���Ȩ,�����������ƺ�����ƽ�ƺ�����
        MapController mMapController = mMapView.getController();  
        //�ø����ľ�γ�ȹ���һ��GeoPoint����λ��΢�� (�� * 1E6)
        GeoPoint point = new GeoPoint((int) (22.522 * 1E6),
                (int) (114.051 * 1E6));  
        //���õ�ͼ���ĵ�
        mMapController.setCenter(point);  
        //���õ�ͼzoom����
        mMapController.setZoom(14);    
        // ��ʼ������ģ�飬ע���¼�����
        mSearch = new MKSearch();
        mSearch.init(app.mBMapMan, new MKSearchListener(){
			public void onGetPoiResult(MKPoiResult res, int type, int error) {
				// ����ſɲο�MKEvent�еĶ���
				if (error != 0 || res == null) {
					Toast.makeText(BaiduDituActivity.this, "��Ǹ��δ�ҵ����", Toast.LENGTH_LONG).show();
					return;
		        }			
				// �ҵ�����·��poi node
                MKPoiInfo curPoi = null;
                int totalPoiNum  = res.getNumPois();
				for( int idx = 0; idx < totalPoiNum; idx++ ) {
				    curPoi = res.getPoi(idx);
                    if ( 2 == curPoi.ePoiType ) {
                        // poi���ͣ�0����ͨ�㣬1������վ��2��������·��3������վ��4��������·
                        mSearch.busLineSearch(mCityName, curPoi.uid);
                    	break;
                    }
				}				
				// û���ҵ�������Ϣ
                if (curPoi == null) {
                    Toast.makeText(BaiduDituActivity.this, "��Ǹ��δ�ҵ����", Toast.LENGTH_LONG).show();
                    return;
                }			
			}
			public void onGetDrivingRouteResult(MKDrivingRouteResult res,
					int error) {
			}
			public void onGetTransitRouteResult(MKTransitRouteResult res,
					int error) {
			}
			public void onGetWalkingRouteResult(MKWalkingRouteResult res,
					int error) {
			}
			public void onGetAddrResult(MKAddrInfo res, int error) {
			}
			public void onGetBusDetailResult(MKBusLineResult result, int iError) {
				if (iError != 0 || result == null) {
					Toast.makeText(BaiduDituActivity.this, "��Ǹ��δ�ҵ����", Toast.LENGTH_LONG).show();
					return;
		        }
				RouteOverlay routeOverlay = new RouteOverlay(BaiduDituActivity.this, mMapView);
			    // �˴���չʾһ��������Ϊʾ��
			    routeOverlay.setData(result.getBusRoute());
			    mMapView.getOverlays().clear();
			    //���·�ߵ�ԭ�е�ͼ��
			    mMapView.getOverlays().add(routeOverlay);
			    //���µ�ͼ
			    mMapView.invalidate();
			    //���ö�������ʾ��·�ߵĿ�ʼ��
			    mMapView.getController().animateTo(result.getBusRoute().getStart());
			}
			@Override
			public void onGetSuggestionResult(MKSuggestionResult res, int arg1) {
				// TODO Auto-generated method stub				
			}
            @Override
            public void onGetRGCShareUrlResult(String arg0, int arg1) {
                // TODO Auto-generated method stub                
            }			
        });        
        // �趨������ť����Ӧ
        mBtnSearch = (Button)findViewById(R.id.search);       
        OnClickListener clickListener = new OnClickListener(){
			public void onClick(View v) {
					SearchButtonProcess(v);
			}
        };     
        mBtnSearch.setOnClickListener(clickListener); 
	}
	void SearchButtonProcess(View v) {
		if (mBtnSearch.equals(v)) {
			//ȡ�ó�����Ϣ
			EditText editCity = (EditText)findViewById(R.id.city);
			//ȡ�ù�����·��Ϣ
			EditText editSearchKey = (EditText)findViewById(R.id.searchkey);
			mCityName = editCity.getText().toString(); 
			mSearch.poiSearchInCity(mCityName, editSearchKey.getText().toString());
		}
	}
	//��ͣ
	@Override
	protected void onPause() {
		BMapApp app = (BMapApp)this.getApplication();
		app.mBMapMan.stop();
		super.onPause();
	}
	//�ָ�
	@Override
	protected void onResume() {
		BMapApp app = (BMapApp)this.getApplication();
		app.mBMapMan.start();
		super.onResume();
	}	
	@Override
	protected boolean isRouteDisplayed() {
		// TODO Auto-generated method stub
		return false;
	}
}