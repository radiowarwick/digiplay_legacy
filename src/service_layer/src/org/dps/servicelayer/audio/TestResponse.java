package org.dps.servicelayer.audio;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;

@XmlAccessorType(XmlAccessType.PROPERTY)
@XmlType(name = "TestResponse", propOrder = {
    "arg1", "arg2"
})
public class TestResponse {
    protected String _arg1;
	protected String _arg2;
	
	@XmlElement(required = true)
	public String getArg1() {
		return _arg1;
	}
	public void setArg1(String arg1_) {
		_arg1 = arg1_;
	}
	@XmlElement(required = true)
	public String getArg2() {
		return _arg2;
	}
	public void setArg2(String arg2_) {
		_arg2 = arg2_;
	}
}