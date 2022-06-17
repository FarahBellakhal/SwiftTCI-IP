//
//  ViewController.swift
//  tcpip
//
//  Created by fransiska on 2017/06/09.
//  Copyright © 2017年 fransiska. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UITextFieldDelegate {

    //MARK: Properties
    
    @IBOutlet weak var ipTextField: UITextField!
    @IBOutlet weak var portTextField: UITextField!
    @IBOutlet weak var connectButton: UIButton!
    @IBOutlet weak var closeButton: UIButton!
    
    var sock:Int32 = -1
    
    //MARK: Default functions
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        ipTextField.delegate = self
        portTextField.delegate = self
        
        let tapRecognizer = UITapGestureRecognizer()
        tapRecognizer.addTarget(self, action: #selector(ViewController.didTapView))
        self.view.addGestureRecognizer(tapRecognizer)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }

    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        //Hide the keyboard
        ipTextField.resignFirstResponder()
        portTextField.resignFirstResponder()
        return true;
    }
    
    @objc func didTapView() {
        self.view.endEditing(true)
    }
    
    func updateConnectButton(connected: Bool) {
        connectButton.isEnabled = !connected
    }
    
    //MARK: Actions
    @IBAction func connectSocket(_ sender: UIButton) {
        /*sock = tcpipSocket_connect(ipTextField.text,Int32(portTextField.text!)!)
        if(sock > 0) {
            updateConnectButton(connected: true)
        }*/
        Tester_init()
        Tester_Connect()
    }
    
    @IBAction func sendMessage(_ sender: UIButton) {
       Tester_SendRoutingActivation()
        readResponse()
        //Tester_DIAG_MESSAGE(1)
        Tester_REGIME_MOTEUR(1)
        readResponse()
        readResponse()
       
    }
    
    @IBAction func closeSocket(_ sender: UIButton) {
       
        updateConnectButton(connected: false)
    }
}

