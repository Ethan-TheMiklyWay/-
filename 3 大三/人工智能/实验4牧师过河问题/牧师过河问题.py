class State:
    def __init__(self, m, c, b, gn, fn, fatherPoint):
        self.m = m  # m��ʾ���Ӱ�����ʦ����
        self.c = c  # c��ʾ���Ӱ���Ұ��������
        self.b = b  # b��ʾ����λ�ã�1Ϊ��࣬0Ϊ�Ҳ�
        self.gn = gn  # g(n)��ʾ��ǰ���ƶ������ǵڼ�����ÿ�ƶ�һ�Σ�move�ͼ�һ
        self.fn = fn  # f(n)��ʾ���ۺ���
        self.fatherPoint = fatherPoint  # ��ʾ���ӵĸ��ڵ�λ��


def main():
    open = []
    close = []
    firstPoint = State(3, 3, 1, 0, 6, 0)
    open.append(firstPoint)
    finalState = 0
    flag = False  # �Ƿ�ɹ��ҵ�·��
    print("�������ÿһ��ѭ����open����е�״̬�������б���ÿһ�����б���ĸ�ֵ�ֱ�Ϊ��Ӱ�"
          "��ʦ��������Ұ��������������λ�ã���ǰ��f(n)")
    # �������еļ�����
    addToOpen = 0
    addToClose = 0
    renewOpen = 0
    closeToOpen = 0
    while len(open) != 0:
        print(list(map(lambda x: [x.m, x.c, x.b, x.fn], open)))
        # �ҵ�open������С���ۺ���λ��fn������¼��index��
        fnlist = list(map(lambda x: x.fn, open))
        index = fnlist.index(min(fnlist))
        fatherState = open[index]
        # ���open���е�ֵ�����뵽close����
        close.append(fatherState)
        addToClose = addToClose + 1
        open.remove(fatherState)
        #    print(fatherState.m,fatherState.c,fatherState.b)
        # ����������״̬���ӵ�open����
        # �ƶ�����ѡ������������ֱ�Ϊ��ʦ����/���ӣ�Ұ���˼���/���ӣ����ƶ�
        MoveSort = [[2, 0, 1], [1, 0, 1], [1, 1, 1], [0, 1, 1], [0, 2, 1],
                    [-2, 0, -1], [-1, 0, -1], [-1, -1, -1], [0, -1, -1], [0, -2, -1]]
        for move in MoveSort:
            # �����µ�״̬����������
            sunM, sunC, sunB = move[0] + fatherState.m, move[1] + fatherState.c, move[2] + fatherState.b
            # �ų�����״̬
            if sunM < 0 or sunM > 3 or sunC < 0 or sunC > 3 or sunB < 0 or sunB > 1:
                continue
            # �����ʦ��������1��2�����µ�״̬����ʦ�����������Ұ��������
            if (sunM == 1 or sunM == 2) and sunM != sunC:
                continue
            # ������״̬��f(n)�����ڵ���ƶ�����+1+�������Ӱ�������
            sunFn = fatherState.gn + 1 + sunM + sunC
            # �ж���״̬�Ƿ�ΪĿ��״̬�����Ϊ�棬������ѭ��
            if sunM == 0 and sunC == 0 and sunB == 0:
                flag = True
                finalState = State(sunM, sunC, sunB, fatherState.gn + 1, sunFn, fatherState)
                break
            # �ж��Ƿ���open����
            for openState in open:
                # �����open�����ҵ�����״̬���ж�֮��Ҫ�˳�
                if [openState.m, openState.c, openState.b] == [sunM, sunC, sunB]:
                    # �жϾɵ�f(s)�Ƿ���µ�f(s)С,�������״̬��fn���޸������ӵĸ�״̬
                    if sunFn < openState.fn:
                        openState.fn = sunFn
                        openState.fatherPoint = fatherState
                        renewOpen = renewOpen + 1
                    break
            # ���û���ҵ����������close������
            else:
                for closeState in close:
                    # �����open�����ҵ�����״̬���ж�֮��Ҫ�˳�
                    if [closeState.m, closeState.c, closeState.b] == [sunM, sunC, sunB]:
                        # �жϾɵ�f(s)�Ƿ���µ�f(s)С,�������״̬��fn���޸������ӵĸ�״̬
                        # ���������뵽open���У���close����ȥ��
                        if sunFn < closeState.fn:
                            closeState.fn = sunFn
                            closeState.fatherPoint = fatherState
                            open.append(closeState)
                            close.remove(closeState)
                            closeToOpen = closeToOpen + 1
                        break
                else:
                    # ��ʱ����open��close���У�Ҫ��ӵ�open����
                    addToOpen = addToOpen + 1
                    open.append(State(sunM, sunC, sunB, fatherState.gn + 1, sunFn, fatherState))
        if flag == True:
            break

    if flag == False:
        print("����û���ҵ����")
        return
    print("\n�ҵ����",
          "\n�ܹ����뵽open���еĽ�������", addToOpen,
          "\n�ܹ����뵽close���еĽ�������", addToClose,
          "\n����open���������", renewOpen,
          "\nclose���еĽ�����·���open���еĴ�����", closeToOpen,
          "\n")
    # �����һ��״̬ѭ���ҵ����е�״̬������¼��һ���µ�list��
    outputList = []
    while finalState.fatherPoint != 0:
        outputList.append(finalState)
        finalState = finalState.fatherPoint
    outputList.reverse()
    # ������
    for i, output in enumerate(outputList, 1):
        print("��ǰΪ�ڣ�", i, "�����ڣ�״̬Ϊ��(", output.m,
              ",", output.c, ",", output.b, ")����ǰ�Ĺ��ۺ���f(n)Ϊ��", output.fn)


if __name__ == "__main__":
    main()
