# list-update-test
ListView C++ Integration Dynamic Length from Separate Thread Test

Questions:
- Why is view not updated when sotre.h:51 is executed?
- In MyView is count changed but onCountChanged not called (unless manually connected with onRowsInserted and onRowsRemoved)
- Why is this error throw?
QObject::connect: Cannot queue arguments of type 'QQmlChangeSet'
(Make sure 'QQmlChangeSet' is registered using qRegisterMetaType().)
