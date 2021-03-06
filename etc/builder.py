from iocbuilder import AutoSubstitution
from iocbuilder.modules.streamDevice import AutoProtocol


class SQC310(AutoSubstitution, AutoProtocol):
    TemplateFile = 'SQC-310.template'
    ProtocolFiles = ['SQC-310.proto']

    def __init__(self, **args):
        self.__super.__init__(**args)
