find_package(Qt5 COMPONENTS Core Gui Qml Widgets)
add_executable(listupdate ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/mymodel.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/resources.qrc)
target_link_libraries(listupdate PRIVATE ${CONAN_LIBS})
target_link_libraries(listupdate PRIVATE Qt5::Core Qt5::Gui Qt5::Qml Qt5::Widgets)
set_target_properties(listupdate
	PROPERTIES 
		AUTOMOC ON
		AUTOUIC ON
		AUTORCC ON)
