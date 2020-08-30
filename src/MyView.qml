import QtQuick 2.15

import my.models 1.0

Item
{
	id: root

	ListView
	{
		id: myView
		anchors.fill: parent
		anchors.centerIn: parent
		model: MyModel
		{
			id: myModel
			onRowsInserted:
			{
				console.log("Rows inserted!")
			}
			onRowsRemoved:
			{
				console.log("Rows removed!")
			}
		}
		delegate: myDelegate
		orientation: Qt.Horizontal

		onCountChanged: 
		{
			console.log("onCountChanged called")
		}

		Component.onCompleted: {
			myModel.onRowsInserted.connect(countChanged)
			myModel.onRowsRemoved.connect(countChanged)
		}
	}

	Component
	{
		id: myDelegate
		Item
		{
			id: numberedBox
			height: 400
			width: 100
			Rectangle
			{
				id: box
				width: parent.width * 0.7
				height: parent.height * 0.8
				anchors.topMargin: parent.height * 0.1
				anchors.horizontalCenter: parent.horizontalCenter
				color:
				{
					if(state === MyModel.Normal)
					{
						return "green"
					}
					if(state === MyModel.Warning)
					{
						return "yellow"
					}
					if (state === MyModel.Alarm)
					{
						return "red"
					}
					return "gray"
				}
			}
			Rectangle
			{
				id: number
				width: parent.width * 0.7
				height: parent.height - box.height
				anchors.top: box.bottom
				anchors.horizontalCenter: parent.horizontalCenter
				color: "#2a323d"
				border.width: 1
				border.color: "#1f222d"
				Text
				{
					anchors.centerIn: parent
					text: index
					font.pixelSize: parent.height * 0.2
					color: "#fff"
				}
			}
		}
	}
}
