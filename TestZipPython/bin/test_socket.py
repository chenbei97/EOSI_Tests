import threading
from socket import socket
import json
import time
from collections import defaultdict
from random import randint
from queue import Queue


class SocketClientManager:
    def __init__(self, port=3000):  # 测试本地链接，只需要提供端口
        self.__port = port
        self.__hostName = "localhost"
        self.__socket = socket()
        self.__isConnected = False

    def connectToHost(self):
        try:
            self.__socket.connect((self.__hostName, self.__port))
            self.__isConnected = True
            print("isconnected")
            self.__run()
        except:
            print("unconnected")
            self.__isConnected = False

    def __run(self):
        if not self.__isConnected:
            return
        self.__thread1 = threading.Thread(target=self.__sendToServer)
        self.__thread2 = threading.Thread(target=self.__recvFromServer)
        self.__thread1.start()
        self.__thread2.start()
        self.__thread1.join()
        self.__thread2.join()

    def __sendToServer(self):
        while self.__isConnected:
            self.__socket.sendall("hello localhost! please respond me "
                                  "'{\"frame\":\"0x0001\",\"repeat\":0}'".encode("utf-8"))
            time.sleep(1)
            print("发送: hello localhost! please respond me '{\"frame\":\"0x0001\",\"repeat\":0}'")
            print("发送线程: ", threading.currentThread())
        '''
        send()：这个函数用于发送数据，它接受一个字节串作为参数，并将其发送到连接的另一端。如果数据太长，它会被分块发送。返回值是实际发送的字节数。
        sendto()：这个函数也用于发送数据，但它还允许指定接收方的地址。这意味着它可以用于无连接协议，如 UDP。sendto() 也返回实际发送的字节数。
        sendall()：这个函数接受一个字节串作为参数，并尝试将其全部发送到连接的另一端。如果数据太长，它会被分块发送。与 send() 不同，sendall() 会持续发送数据，直到所有数据都被发送出去，或者发生错误。
        sendfile()：这个函数用于将文件的内容发送到连接的另一端。它接受一个文件描述符、一个可选的偏移量和一个可选的字节数作为参数。如果偏移量或字节数未指定，那么整个文件将被发送。返回值是实际发送的字节数。
        sendmsg()：这个函数允许发送更复杂的数据结构，如包含多个数据段和/或辅助数据的消息。它通常用于 SCM_RIGHTS 等高级功能，这些功能在基本套接字操作中不可用。返回值是实际发送的字节数。
        '''

    def __recvFromServer(self):
        while self.__isConnected:
            msg = self.__socket.recv(1024)
            print("接收: ", msg.decode("utf-8"))
            print("接收线程: ", threading.currentThread())
        '''
        recv()：这是最基本的接收数据函数，它接收指定的最大字节数，并返回一个字节串。如果接收的数据超过了指定的字节数，那么数据可能会被截断。
        recvmsg()：这个函数返回一个包含数据和可选的辅助数据的消息对象。这个功能比recv()更强大，因为它可以处理更复杂的数据结构。
        recv_into()：这个函数和recv()类似，但是它允许你提供一个缓冲区，数据会被填充到这个缓冲区中。这个函数返回实际接收的字节数。
        recvmsg_into()：这个函数和recvmsg()类似，但是它允许你提供一个缓冲区，数据会被填充到这个缓冲区中。这个函数返回实际接收的字节数。
        recvfrom()：这个函数类似于recv()，但是它返回一个元组，包含接收到的数据和发送方的地址。这对于无连接协议（如UDP）非常有用。
        recvfrom_into()：这个函数类似于recvfrom()，但是它允许你提供一个缓冲区，数据会被填充到这个缓冲区中。这个函数返回实际接收的字节数和发送方的地址。
        '''


def test_client():
    m = SocketClientManager()
    m.connectToHost()


class Parse0x0000Fields:
    # 询问设备号的命令0x0001,需要回复设备号
    def __init__(self):
        self.__fields = ["channel", "objective", "group", "count", "duration",
                         "end", "is_schedule", "view", "wellsize", "total", "start"]
        self.__channel = "channel"
        self.__objective = "objective"
        self.__group = "group"
        self.__count = "count"
        self.__duration = "duration"
        self.__end = "end"
        self.__is_schedule = "is_schedule"
        self.__view = "view"
        self.__wellsize = "wellsize"
        self.__total = "total"
        self.__start = "start"

        # 以下字段不属于json会传输的字段,只是方便用
        self.__x = "x"
        self.__y = "y"
        self.__order = "order"

    @property
    def x(self):  # 不可修改
        return self.__x

    @property
    def y(self):  # 不可修改
        return self.__y

    @property
    def order(self):  # 不可修改
        return self.__order

    @property
    def start(self):  # 不可修改
        return self.__start

    @property
    def wellsize(self):  # 不可修改
        return self.__wellsize

    @property
    def total(self):  # 不可修改
        return self.__total

    @property
    def is_schedule(self):  # 不可修改
        return self.__is_schedule

    @property
    def view(self):  # 不可修改
        return self.__view

    @property
    def end(self):  # 不可修改
        return self.__end

    @property
    def duration(self):  # 不可修改
        return self.__duration

    @property
    def count(self):  # 不可修改
        return self.__count

    @property
    def group(self):  # 不可修改
        return self.__group

    @property
    def objective(self):  # 不可修改
        return self.__objective

    @property
    def channel(self):  # 不可修改
        return self.__channel

    @property
    def fields(self):  # 不可修改
        return self.__fields


class Parse0x0001Fields:
    # 询问设备号的命令0x0001,需要回复设备号
    def __init__(self):
        self.__equipment_number = "equipment_number"

    @property
    def equipment_number(self):  # 不可修改
        return self.__equipment_number


class Parse0x0002Fields:
    # 客户端发送0x0002,和一个坐标,需要返回原坐标、路径
    def __init__(self):
        self.__point_x = "point.x"
        self.__point_y = "point.y"
        self.__path = "path"

    @property
    def point_x(self):  # 不可修改
        return self.__point_x

    @property
    def point_y(self):
        return self.__point_y

    @property
    def path(self):
        return self.__path


class ParseManager:
    def __init__(self):
        self.__frame = "frame"
        self.__repeat = "repeat"
        self.__field0x0000 = Parse0x0000Fields()
        self.__field0x0001 = Parse0x0001Fields()
        self.__field0x0002 = Parse0x0002Fields()
        self.__parseFunctions = {
            "0x0000": self.__parse0x0000,
            "0x0001": self.__parse0x0001,
            "0x0002": self.__parse0x0002
        }
        self.__socket = None

    def setSocket(self, sock: socket):
        self.__socket = sock
        # 外部传入客户端套接字指针,这个套接字用于解析函数内使用可以给客户端回复消息

    def __parse0x0000(self, msg: dict):
        # 这里只是单纯的打印所有字段的内容，实际要根据这些内容开始启动实验流程，后续再写
        # ----------------------------------------------------------------------
        for field in self.__field0x0000.fields:
            if field == self.__field0x0000.group:
                groups = msg[field]
                groupPts = []
                for group in groups:
                    # print(group.keys())  # 这里可以拿到组的名称,有必要的话
                    for pointlist in group.values():
                        # print(pointlist)
                        pts = [() for _ in range(len(pointlist))]  # 生成指定长度的列表
                        for point in pointlist:
                            x = point[self.__field0x0000.x]
                            y = point[self.__field0x0000.y]
                            order = point[self.__field0x0000.order]
                            pts[order] = (x, y)  # 根据这个点的次序存放到列表的对应位置去
                        # print(pts) # 这里就拿到了这个组的所有点,且排好序
                    groupPts.append(pts.copy())  # 大列表拿到所有组的点,注意要深拷贝
                print(groupPts)  # 所有组的所有点
            else:
                print(msg[field])
        # ----------------------------------------------------------------------

        reponse = defaultdict()
        reponse[self.frameStr] = msg[self.frameStr]
        reponse[self.repeatStr] = 0  # 0x0000命令不需要重发,不需要返回任何值
        self.__socket.sendall(json.dumps(reponse).encode("utf-8"))  # utf-8发出,这样上位机解析也是根据utf-8来解析

    def __parse0x0001(self, msg: dict):
        reponse = defaultdict()
        reponse[self.frameStr] = msg[self.frameStr]
        reponse[self.repeatStr] = 0
        reponse[self.field0x0001.equipment_number] = 1
        print("回复: ", json.dumps(reponse))
        self.__socket.sendall(json.dumps(reponse).encode("utf-8"))

    def __parse0x0002(self, msg: dict):
        frame = msg[self.frameStr]
        point_x = msg[self.field0x0002.point_x]
        point_y = msg[self.field0x0002.point_y]

        reponse = defaultdict()
        path = r"path/to/image/" + str(randint(1, 100))  # 模拟,path后续要改为真实的算法得到的图片

        # ----------------模拟超时使用,后续可以注释掉--------------
        end_time = msg["end_time"]  # 为了模拟,在拿到客户端发来的msg后增加了这个字段
        # 这里模拟一个比较耗时的操作,例如点击移动拍图调用算法返回这些
        delay = 3  # randint(self.maxdelay - 1, self.maxdelay + 1)
        # time.sleep(delay)  # 上位机会等待这次结果,假设拍图时间最多4s就可以完成,上位机只会等待4s,随机超时
        diff = time.time() - end_time
        if diff > 0:  # 执行超时
            reponse[self.frameStr] = frame
            reponse[self.repeatStr] = 1  # 要求重发(上位机设定超时时间长一些，尽量不会超时；另外中间层最好不设置要求重发)
        else:
            # ----------------------------------------------------------
            reponse[self.frameStr] = frame  # 只有这部分保留,逐坐标拍照需要发送的参数
            reponse[self.repeatStr] = 0
            reponse[self.field0x0002.point_x] = point_x
            reponse[self.field0x0002.point_y] = point_y
            reponse[self.field0x0002.path] = path

        # ----------------模拟超时使用,后续可以注释掉--------------
        text = "超时" if diff > 0 else "没超时"
        response = json.dumps(reponse)
        print(f"回复: {response} 执行时间: {delay}s 状态: {text}")
        # ----------------------------------------------------------

        self.__socket.sendall(response.encode("utf-8"))

    @property
    def maxdelay(self):
        return 5  # 如果服务端程序执行超过5s,即客户端等待超过5s

    @property
    def frameStr(self):
        return self.__frame

    @property
    def repeatStr(self):
        return self.__repeat

    @property
    def field0x0001(self):
        return self.__field0x0001

    @property
    def field0x0002(self):
        return self.__field0x0002

    @property
    def parseFunctions(self):
        return self.__parseFunctions

    def parseFunction(self, frame: str):  # 返回这个帧对应的函数指针
        return self.__parseFunctions[frame]


class SocketServerManger:
    def __init__(self, port=3001):  # 测试本地链接，只需要提供端口
        self.__port = port
        self.__hostName = "localhost"
        self.__msgQueue = Queue()
        self.__socket = socket()
        self.__socket.bind((self.__hostName, self.__port))
        self.__isConnected = False
        self.__parser = ParseManager()
        self.__parseFunctions = self.__parser.parseFunctions

    def waitForConnected(self, blockSecs=50):
        print("wait for connection...")
        self.__socket.settimeout(blockSecs)  # 必须在这里设置,下边的listen设置不起作用会一直阻塞
        try:
            self.__socket.listen()
            self.client, client_addr = self.__socket.accept()
            print("connect successful!")
            self.__isConnected = True
            self.__parser.setSocket(self.client)  # 把客户端指针给解析类使用
            self.__run()
        except:
            self.__isConnected = False
            print("have no connection")

    def __run(self):
        if not self.__isConnected:
            return
        self.__thread1 = threading.Thread(target=self.__sendToClient)
        self.__thread2 = threading.Thread(target=self.__recvFromClient)
        self.__thread3 = threading.Thread(target=self.__parseMessage)
        self.__thread1.start()
        self.__thread2.start()
        self.__thread3.start()
        self.__thread1.join()
        self.__thread2.join()
        self.__thread3.join()

    def __sendToClient(self):
        while self.__isConnected:  # 这个函数不需要任何实现,因为回复信息已经在self.__parseMessage做了
            pass  # 为了逻辑清晰/测试使用,服务端想要测试发给客户端可以在这写些东西,一般不需要写

    def __recvFromClient(self):
        while self.__isConnected:
            msg = self.client.recv(10240).decode("utf-8")  # 字符串形式,0x0000命令长度>1024
            self.__msgQueue.put(msg)  # 放入消息队列（可能包含多条命令）
            print("接收: ", msg, " 队列长度: ", self.__msgQueue.qsize())
            # recv(1024)可以保证要么是一条命令或者是多条命令,都是完整的,不会出现破碎的情况
            # 所以无需考虑消息破碎还要进行前后衔接的问题,10240的长度足够完整的收发所有命令

    def __parseMessage(self):
        while self.__isConnected:
            while not self.__msgQueue.empty():
                msg = self.__msgQueue.get()  # 可能是多条命令,拆分的方法是{}一条完整命令
                print("取出: ", msg)
                if msg.count("0x0000"):  # 0x0000命令特殊处理.{0x0000}{0x0000}...不能通过{}分开,因为0x0001内部还有{}
                    msg_dict = json.loads(msg)  # 但是0x0000不可能出现{0x0000}{0x0000}...的情况,只会有1个
                    self.__parseFunctions["0x0000"](msg_dict)
                else:
                    while msg:  # msg={0x0001}{0x00001}..,利用{}一对对寻找
                        idx1 = msg.find("{")  # 对于嵌套型的0x0000命令会出问题 不能通过{}来确定是完整命令
                        idx2 = msg.find("}")  # 不过客户端不可能非常快速的发0x0000只会发1次,所以这里也不用管
                        # print(f"idx1 = {idx1} idx2 = {idx2}")
                        if idx2 > idx1 and idx1 > -1:
                            command = msg[idx1:idx2 + 1]  # 取出来的
                            if idx1 > 0:
                                other = msg[0:idx1] + msg[idx2 + 1:]
                            else:
                                other = msg[idx2 + 1:]
                            msg = other  # 剩下的
                            msg_dict = json.loads(command)  # 字符串变成字典
                            frame = msg_dict[self.__parser.frameStr]  # 客户端一定带有frame字段

                            # ----------------模拟超时使用,后续可以注释掉--------------
                            if frame == "0x0002":  # 额外增加end_time字段
                                msg_dict["end_time"] = time.time() + self.__parser.maxdelay
                            # -----------------------------------------------------------

                            print("msg_dict = ", msg_dict, " 队列长度: ", self.__msgQueue.qsize())
                            self.__parseFunctions[frame](msg_dict)  # 放入解析类内的解析函数解析
                            # time.sleep(0.02)
                        else:
                            break


def test_server():
    # C++是客户端,主动连接服务端中间层，因为中间层是被启动的不会主动连接C++
    # 所以真正的写法是用服务端的写法
    m = SocketServerManger()
    m.waitForConnected()


if __name__ == '__main__':
    runClient = False
    test_client() if runClient else test_server()
