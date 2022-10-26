====使用前请先阅读本文====
#压缩包文件结构说明
  apk -- 测试APK
  code -- 演示程序源码
  doc -- 开发文档
  libs -- 核心库
  ReadMe.txt
  
  
 # 使用说明
 1.打开APP(初次打开应用，需要授予对应权限)
 2.拷贝升级文件到手机固定的存放位置
   2.1 如果手机系统是Android 10.0+，放到/Android/data/com.jieli.otasdk/files/com.jieli.otasdk/upgrade/
   2.2 如果手机系统是Android 10.0以下，放到/com.jieli.otasdk/upgrade/
 3.连接升级目标设备
 4.选择目标的升级文件，开始OTA升级

 
 # 升级方式说明
 1.客户可以选择基于jl_bt_ota的SDK开发，参考com.jieli.otasdk/tool/ota/。
 
 设备通讯方式： 默认是BLE，可选SPP，需要固件支持。
 双备份支持BLE/SPP, 单备份目前只支持BLE。
 
 
 # OTA升级参数说明
 参考OTAManager
   val bluetoothOption = BluetoothOTAConfigure()
   //选择通讯方式
   bluetoothOption.priority = BluetoothOTAConfigure.PREFER_BLE
   //是否需要自定义回连方式(默认不需要，如需要自定义回连方式，需要客户自行实现)
   bluetoothOption.isUseReconnect = !JL_Constant.NEED_CUSTOM_RECONNECT_WAY
   //是否启用设备认证流程(与固件工程师确认)
   bluetoothOption.isUseAuthDevice = JL_Constant.IS_NEED_DEVICE_AUTH
   //设置BLE的MTU
   bluetoothOption.mtu = BluetoothConstant.BLE_MTU_MIN
   //是否需要改变BLE的MTU
   bluetoothOption.isNeedChangeMtu = false
   //是否启用杰理服务器(暂时不支持)
   bluetoothOption.isUseJLServer = false
   //是否需要调整BLE的MTU大小(默认不调整MTU，如果需要调整，请配合mtu属性设置)
   bluetoothOption.isNeedChangeMtu = false
   //配置OTA参数
   configure(bluetoothOption)
 
 # Logcat开关说明
 1.开关LOG 可以使用JL_Log.setIsLog(boolean bl)设置
 2.保存LOG到本地 前提是Log已打开，并调用JL_Log.setIsSaveLogFile(boolean bl)设置
	2.1 若开启保存，退出应用前记得关闭保存Log文件。
	2.2 Log保存位置：
	  2.2.1 如果是Android 10.0+，放到./Android/data/com.jieli.otasdk/files/com.jieli.otasdk/logcat/
	  2.2.2 如果是Android 10.0以下，放到/com.jieli.otasdk/logcat/
	3. Log 文件每次开启保存文件都会创建， 所以为了避免太多 Log 文件影响， 注意定期清理
	4. Log 文件命名格式： ota_log_app_[时间戳].txt
 3.出现 OTA 问题， 请提供以下资料
	1. 简单描述复现 OTA 问题的步骤
	2. 提供出现 OTA 问题的时间戳最接近的 Log 文件， 可以多份， 并说明 OTA 问题的时间戳
	3. 最好提供视频或者问题截图
	
	
 # 版本渠道说明
 1.Debug版本默认开启打印，可以选择测试配置。
	1.1 是否启用设备认证(默认开启)
	1.2 是否HID设备(默认关闭，回连方式有变化，因为HID设备系统会主动回连)
	1.3 是否自定义回连方式(默认关闭，如需要自定义回连方式，需要客户自行实现)
 2.Release版本默认关闭打印，不显示测试配置。
 
 # 开源地址
 1.国外用户可以访问 GitHub(https://github.com/Jieli-Tech/Android-JL_OTA)
	1. 用户可以在 issues(https://github.com/Jieli-Tech/Android-JL_OTA/issues)提问， 我司开发者会及时提供回复
	2. 用户也可以进入我司的开源群（钉钉： 搜索“AC63/69 杰理开源社区”） ， 找到对应负责人进行咨询
 2.国内用户可以访问 Gitee(https://gitee.com/Jieli-Tech/Android-JL_OTA)
	1. 用户可以先参考杰理 OTA 库答疑(https://gitee.com/Jieli-Tech/Android-JL_OTA/wikis/%E6%9D%B0%E7%90%86OTA%E5%BA%93%20%E7%AD%94%E7%96%91)
	2. 用户可以在 issues(https://gitee.com/Jieli-Tech/Android-JL_OTA/issues) 提问， 我司开发者会及时提供回复
	3. 用户也可以进入我司的开源群（钉钉： 搜索“AC63/69 杰理开源社区”） ， 找到对应负责人进行咨询
 3.用户可以关注下我司的官方账号
	1. GitHub 账号： ZhuHai Jieli Technology Co.,Ltd(https://github.com/Jieli-Tech)
	2. Gitee 账号： 珠海杰理科技(https://gitee.com/Jieli-Tech)
 
 
 